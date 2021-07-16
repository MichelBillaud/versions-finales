pdfs = livret.pdf 


all:   
	(cd ../Sources; make)
	make all_

all_ : $(pdfs) 


%.pdf: %.tex
	rubber -m xelatex  $<

clean:
	rubber --clean livret
	$(RM) *~ *.bak
	(cd sources ; make clean)

mrproper: clean
	$(RM) $(pdfs)
	(cd ../Sources ; make mrproper)


livret.pdf: $(wildcard chap-*.tex) $(wildcard sources/*.run)

