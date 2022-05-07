//
// an Assembler for the sim16 machine
//
// M Billaud, Dec 2012
// michel.billaud@u-bordeaux1.fr
//


var opTable = {
    word : { fn : 0, fmt : 2 },
    loadi : { fn : 0, fmt : 1 },
    load : { fn : 1, fmt : 1 },
    loadx : { fn : 2, fmt : 1 },
    store : { fn : 3, fmt : 1 },
    storex : { fn : 4, fmt : 1 },
    add : { fn : 5, fmt : 1 },
    sub : { fn : 6, fmt : 1 },
    jmp : { fn : 7, fmt : 1 },
    jneg : { fn : 8, fmt : 1 },
    jzero : { fn : 9, fmt : 1 },
    jmpx : { fn : 10, fmt : 1 },
    call : { fn : 11, fmt : 1 },
    halt : { fn : 12, fmt : 1 }
}

// same array, indexed by function number
var opsByFn = new Array()
for (var i in opTable)
{
    if (opTable[i].fmt != 2) {
	opsByFn[opTable[i].fn]  = opTable[i]
	opsByFn[opTable[i].fn].name  = i
    }
}

function unassemble(word)
{
    var op = (word >> 12) & 0xF
    var s  = word  & 0xfff
    return opsByFn[op].name + " " + toHex(s,3)
}

function validLabel(label)
{
    return label.match(/^[a-zA-Z](\w)*$/)
}


function validDecimalNumber(num)
{
    return num.match(/^[+-]?[0-9]+$/)
}

function validHexaDecimalNumber(num)
{
    return num.match(/^0x[0-9a-fA-F]+$/)
}

function validNumber(num)
{
    return validDecimalNumber(num) || 
	validHexaDecimalNumber(num)
}

function validOpcode(opcode)
{
   return (opTable[opcode] != null)
}


function Symbol(symbol,line,value) {
    this.symbol = symbol
    this.line   = line
    this.value  = value
}

function Patch(symbol,line,location,fmt) {
    this.symbol = symbol
    this.line   = line
    this.location  = location
    this.fmt   = fmt  // 1:instruction 2:VAL
}


function Assembler() 
{
    this.source = ""
    this.listing = ""
    this.debug = ""

    this.object = null
    this.location = 0

    this.assemble = function (aText) {
	this.source = aText
	this.location = 0
	this.errors =  0
	this.object = new Array()
	this.listing = new Array()
	this.debug = new Array()
	this.symbols = new Array()
	this.patches = new Array()

	this.listing.push("Line\tAddr.\tSource\n")
	var lines = this.source.split("\n")
	for (var i in lines) {
	    var n = parseInt(i)+1
	    this.parseLine(n, lines[i])
	}
	this.applyPatches()
	this.listing.push("")
	this.listing.push("Symbol\tValue\tLine")
	this.listing.push("------\t-----\t----")
	for (var s in this.symbols) {
	    var a = toHex(this.symbols[s].value,3)
	    this.listing.push(s+"\t"
			      +"0x"+a+"\t"
			      +this.symbols[s].line)
	}
	this.listing.push("------\t-----\t----")
    }

    this.parseLine = function(n,aLine) {
	this.listing.push(n+"\t0x" + toHex(this.location,3)
			  +"\t" + aLine)


	// suppression commentaires et espaces à droite
	var line = aLine.replace(/#.*$/,'').replace(/\s+$/,'')  

	var tokens = line.split(/\s+/)
	var label  = tokens[0]
	var opcode = tokens[1]
	var arg    = tokens[2]
	
	if (opcode == null) {
	    opcode = "";
	}

	if (arg == null) {
	    arg = "";
	}

	this.debug.push("==>  label = "+label)
	this.debug.push("==> opcode = "+opcode)
	this.debug.push("==>    arg = "+arg)

	// turning to lowercase
	label  = label.toLowerCase()
	opcode = opcode.toLowerCase()
	arg    = arg.toLowerCase()

	if (label != "") {
	    this.debug.push("processing label " +label)
	    if (validLabel(label)) {
		if (this.symbols[label] == null) {
		    this.symbols[label] = new Symbol(label, n,this.location)
		    this.debug.push("New symbol " + label +
				      " location=" + this.location)
		} else {
		    this.listing.push("Symbol "+label+" already defined line "
				      + this.symbols.line)
		    this.errors ++
		}
	    } else {
		this.listing.push("Invalid label '"+label+"'")
		this.errors ++
	    }
	}
	
	if (opcode != "") {
	    this.debug.push("processing opcode " +opcode)
	    if (validOpcode(opcode)) {
		var fmt = opTable[opcode].fmt;
		var fn = opTable[opcode].fn;
		var inst = (fn << 12)	    
		switch (fmt) {
		case 1:
		case 2:
		    if (validNumber(arg)) {
			if (fmt==1)
			    inst |=   (arg & 0xFFF) 
			else
			    inst = arg & 0xFFFF
			this.object[this.location] = inst
			this.debug.push("instruction generated : 0x" +
					toHex(inst,4))
			this.location++
		    } else if (validLabel(arg)) {
			this.object[this.location] = inst
			this.debug.push("instruction generated : 0x" 
					+toHex(inst,4)
					+ " + symbol " +arg)
			// generate patch
			this.patches.push(new Patch(arg,n,this.location,fmt))
			this.location++
		    } else {
			this.listing.push("E: Invalid operand "+arg)
			this.errors ++
		    }
		    break;
		}
	    } else {
		// opcode is invalid
		this.listing.push("E: opcode '"+opcode
				  +"' is invalid")
		this.errors ++
	    }
	}	
    }

    this.applyPatches = function() {
	for (var i in this.patches) {
	    var symbol = this.patches[i].symbol
	    if (this.symbols[symbol] == null) {
		this.listing.push("E: Undefined symbol '"+symbol
				  +"' line "+this.patches[i].line)
		this.errors ++
	    } else {
		var value = this.symbols[symbol].value
		var location = this.patches[i].location 
		var m = this.patches[i].fmt == 1 
		    ? (value & 0xFFF) 
		    : value
		this.object[location] += m
		this.debug.push("Location "+ location +
				" patched with value " + value +
				"to 0x" +  toHex(this.object[location],8) +
				" fmt " + this.patches[i].fmt)
	    }
	}
    }
    
    this.dump = function() 
    {
	print("source   -> ")
	var lines = this.source.split("\n")
	for (var i in lines) {
	    var n = parseInt(i)+1
	    print(n + "\t" + lines[i])
	}	
	print ("listing -> ")
	for (var i in this.listing) {
	    print( this.listing[i])
	}
	print ("debug -> ")
	for (var i in this.debug) {
	    print( this.debug[i])
	}	
	print ("object  -> ")
	for (var i in this.object) {
	    print(i + ":" + this.object[i].toString(16))
	}
	print("location -> " + this.location)
	print("symbols ->")
	for (var i in this.symbols) {
	    print(i + ":" + this.symbols[i])
	}
	print("patches ->")
	for (var i in this.patches) {
	    print(i + ":" + this.patches[i])
	}	   
    }
}
