//
// a Simulator for the SSEM "baby" computer
// user interface functions
//
// M Billaud, April 2012
// michel.billaud@u-bordeaux1.fr
//


window.onload = onLoad

function onLoad() {
    document.getElementById('b_asm').onclick   = do_assemble
    document.getElementById('b_step').onclick  = do_step
    document.getElementById('b_run').onclick   = do_run
    document.getElementById('b_pause').onclick = do_pause
    document.getElementById('b_setci').onclick = do_setci
    document.getElementById('b_load').onclick  = do_load
    enableLoadButton(false)

    // global vars
    // output divs
    memory    =  document.getElementById('memory')
    registers =  document.getElementById('registers')
    status    =  document.getElementById('status')
    paper     =  document.getElementById('paper')
    editor    =  document.getElementById('buffer')

    // input fields
    ci        =  document.getElementById('ci')
    delay     =  document.getElementById('delay')
    
    a = new Assembler()
    s = new Simulator()
    showMachine()
}

function enableLoadButton(yes) {
    document.getElementById('b_load').disabled = ! yes
}

function showMachine()
{

    memory.innerHTML = s.MemoryHTML()
    registers.innerHTML =  s.RegistersHTML()
    status.innerHTML =  s.StatusHTML()
}

function do_assemble() {
    a.assemble(editor.value)
    
    enableLoadButton(a.errors == 0)

    var message =  ( a.errors == 0
		     ? "Successful<br/>" 
		     : "Failed: " +  a.errors + " errors detected<br/>"
		   )
   
    message += "<pre>\n"
    for(var i in a.listing) {
	message += a.listing[i] + "\n"
    }

    var showDebug = 0
    if (showDebug) {
	message += "<h3>debug</h3>"
	message += "<pre>\n"
	for(var i in a.debug) 
            message += a.debug[i] + "\n"
	message += "</pre>\n"
    }
    paper.innerHTML = message
}

function do_load() {
    s.load(a.object)
    showMachine()
 }

function do_step() {
    s.step()
    showMachine()
}

function do_setci() {
    var v = parseInt(ci.value)
    s.c.ci = v
    s.status = "CI set to " + toHex(v,3)
    showMachine()
}

function do_run() {
    // set the delay
    s.delay =  parseInt(delay.value)
    // set mode to auto
    s.c.auto = 1
    // and launch step
    do_run_step()
}

function do_run_step() {
    s.step()
    if (s.c.auto == 1) {
	showMachine()
	s.timer = setTimeout("do_run_step()", s.delay)
    } else {
	s.status = "Halted"
	showMachine()
    }
}

function do_pause() { 
    clearTimeout(s.timer)
    s.status = "Paused"
    showMachine()
}
