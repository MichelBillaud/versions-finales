asm = ../../Sim16/asm16
sim = ../../Sim16/sim16 

tests = valeur-absolue somme-entiers somme-tab tri-tableau fib

all:  $(tests:=.run)

%.hex: %.asm
	$(asm) $<

%.run: %.hex
	$(sim) -s $< >$@

clean:
	$(RM) *~ *.hex *.lst *.run
