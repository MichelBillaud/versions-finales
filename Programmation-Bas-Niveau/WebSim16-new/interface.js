//
// user interface functions
//
// M Billaud, Mars 2012
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
    alert("qqqq")
    showMachine()
    s.step_by_step = 0
    running = 0
}

function enableLoadButton(yes) {
    document.getElementById('b_load').disabled = ! yes
}

function showMachine()
{
    memory.innerHTML    = s.MemoryHTML()
    registers.innerHTML = s.RegistersHTML()
    status.innerHTML    = s.StatusHTML()
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
    step_by_step = 1
    showMachine()
 }

function do_step() {
    s.step_by_step = 1
    clearInterval(s.interval)
    s.step()
    showMachine()
}

function do_setci() {
    var v = parseInt(ci.value)
    s.c.ci = v
    s.status = "CI set to " + toHex(v,3)
    s.step_by_step = 1
    clearInterval(s.interval)
    showMachine()
}

function do_run() {
    clearInterval(s.interval)
    s.delay =  parseInt(delay.value)
    s.step_by_step = 0
    s.interval = setInterval("run_step()", s.delay)
}

function run_step() {
    s.step()
    if (s.c.halted) {
	s.status = "sim halted"
	clearInterval(s.interval)
	s.step_by_step = 1
    } 
    showMachine()	
}

function do_pause() { 
    clearInterval(s.interval)
    s.step_by_step = 1
    s.status = "Paused"
    showMachine()
}
