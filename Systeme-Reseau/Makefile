OUTPUTDIR = Output


INPUTS = /usr/local/share/texmf:Latex:

CMD = TEXINPUTS=$(INPUTS)  xelatex -output-directory $(OUTPUTDIR) 

$(OUTPUTDIR)/polycop-psr.pdf:
	$(CMD) polycop-psr
	$(CMD) polycop-psr

clean:
	(cd PROGS ; make clean)
	(cd Latex; make clean)
	$(RM) *~
	$(RM) */*.aux */*.toc */*.log */*.fls */*.bbl */*.bib */*.blg */*.idx */*.out */\#*

mrproper: clean
	(cd PROGS ; make mrproper)
	(cd Latex; make mrproper)

