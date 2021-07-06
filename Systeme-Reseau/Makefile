date := $(shell date "+%Y-%m-%d")
pdf = psr-$(date).pdf


$(pdf): LATEX/polycop-psr.pdf
	cp $< $@

LATEX/polycop-psr.pdf:
	(cd LATEX ; make polycop-psr.pdf)

publish: LATEX/polycop-psr.pdf
	(cd LATEX ; make publish)

clean:
	(cd PROGS ; make clean)
	(cd LATEX; make clean)
	$(RM) *~

mrproper: clean
	(cd PROGS ; make mrproper)
	(cd LATEX; make mrproper)
