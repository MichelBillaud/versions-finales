//
// a Simulator for the Sim16 computer
//
// M Billaud, Dec 2012
// michel.billaud@u-bordeaux1.fr
//
// 2013-03-16 Memory reset before loading program

function Computer ()
{
    this.m = new Array()
    this.memsize = 128
    //for (var i = 0; i < this.memsize; i++)
    //	this.m[i] = 0

    this.resetMemory = function() {
	for (var i = 0; i < this.memsize; i++)
	    this.m[i] = 0
    }
    this.resetMemory()

    this.resetRegisters = function() {
	this.a    = 0
	this.ci   = 0
	this.pi   = 0
	this.halted = 0
	this.error  = 0
    }
    this.resetRegisters()
 
    this.checkAddress = function(address, explanation) {
	if (address < 0 || address >= this.memsize) {
	    this.halted = 1
	    this.error  = 1
	    throw "Illegal memory access (" +
		explanation + " at 0x" + toHex(address,3)+ ")"
	}
    }

    this.step = function() {
	this.halted = 0
        this.error  = 0
	// fetch
	this.checkAddress(this.ci, "fetching")
	this.pi = this.m[this.ci]
	var op = (this.pi >> 12) & 0xF
	var s  = (this.pi      ) & 0xfff
	this.ci += 1
	// decode & execute
	switch (op) {
	case 0 : // 
	    this.a = (s & 0x800) == 0 ? s : (s | 0xF000) 
	    break
	case 1 : 
	    this.checkAddress(s,"load adr")
	    this.a =  this.m[s] 
	    break
	case 2 : 
	    this.checkAddress(s,"loadx ind")
	    this.checkAddress(this.m[s],"loadx ind")
	    this.a =  this.m[this.m[s]] 
	    break
	case 3 : 
	    this.checkAddress(s,"store adr")
	     this.m[s] = this.a 
	    break
	case 4 : 
	    this.checkAddress(s,"storex ind")
	    this.checkAddress(this.m[s],"loadx ind")
	    this.m[this.m[s]]  = this.a 
	    break
	case 5:
	    // les entiers javascript sont 32 bits
	    this.checkAddress(s,"add operand")
	    this.a = (this.a + this.m[s]) & 0xFFFF
	    break
	case 6:
	    // les entiers javascript sont 32 bits
	    this.checkAddress(s,"sub operand")
	    this.a = (this.a - this.m[s]) & 0xFFFF
	    break
	case 7: // jmp
	    this.checkAddress(s,"jmp address")
	    this.ci = s
	    break
	case 8: // jneg
	    this.checkAddress(s,"jneg address")
	    if (this.a & 0x8000) {
		this.ci = s
	    }
	    break
	case 9: // jzero
	    this.checkAddress(s,"jneg address")
	    if ((this.a & 0xFFFF) == 0) {
		this.ci = s
	    }
	    break
	case 10: // jmpx
	    this.checkAddress(s,"jmpx ind")
	    this.checkAddress(this.m[s],"jmpx ind")
	    this.ci = this.m[s]
	    break
	case 11: // call
	    this.checkAddress(s,"call addr")
	    this.m[s] = this.ci
	    this.ci = s+1
	    break
	case 12: // halt
	    this.halted = 1
	    this.ci --
	    break
	}
    } // end method step()
}

// ---------------------------------------------

function Simulator ()
{
    this.c            = new Computer()
    this.status       = "Power is on"
    this.step_by_step = 1
    this.interval     = null

    this.load = function (object) {
        this.c.resetMemory()
	for (var i in object)
	    this.c.m[i] = object[i]
	this.c.resetRegisters()
    }

    this.step = function () {
	try {
	    this.c.step()
	} catch (error) {
	    this.c.status = error
	}
    }

    this.MemoryHTML = function() {
        var cols = 4
        var lines = this.c.memsize / cols
	var r = "<h2>Memory</h2>\n<pre>\n";
	for (var l=0; l<lines; l+=1) {
	    var line = ""
	    for (var c=0; c<cols; c++) {
		var i = l + lines * c
		var m = toHex(i,3)+":"+toHex(this.c.m[i],4)+" "
		if (i == this.c.ci) 
		    line += "<b>"+m+"</b>"
		else 
		    line += m
	    }
	    r += line + '\n'
	} 
	return r
    } // end method MemoryHTML()

    this.RegistersHTML = function() {
	var r = ("<h2>Registers</h2><tt>"
                 + (this.c.halted ? "HALT " : " ") 
	       + "A=["   +toHex(this.c.a,4)  + "] " 
	       + "CI=[" + toHex(this.c.ci,4) + "] "
	       + "(" + unassemble(this.c.m[this.c.ci]) + ")</tt>"
	      )
	return r
    } // end method RegistersHTML()

    this.StatusHTML = function() {
	return "<h2>Status</h2>" +
	    (this.c.error ? "Failure. " : " ") +
	    this.status
    }
} 
