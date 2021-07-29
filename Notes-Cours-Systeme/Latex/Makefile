PDF += notes-cours-systeme.pdf
PDF += transparents-cours.pdf

XELATEX = xelatex -output-directory ../Output

all: $(addprefix ../Output/, $(PDF))

../Output/%.pdf: %.tex
	$(XELATEX) $<
	$(XELATEX) $<




mrproper: clean
	$(RM) *.pdf

clean:
	$(RM) *~ 
	(cd ../Output; $(RM) *.aux *.log *.toc *.nav *.snm *.out)

../Output/notes-cours-systeme.pdf: notes-cours-systeme.tex Style/bouquin.sty

../Output/transparents-cours.pdf: transparents-cours.tex  Style/transparents.sty

