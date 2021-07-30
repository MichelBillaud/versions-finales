PDF += notes-cours-systeme.pdf
PDF += transparents-cours.pdf

XELATEX = xelatex -output-directory ../Output

all: $(addprefix ../Output/, $(PDF))

# ../Output/%.pdf: %.tex
# 	$(XELATEX) $<
# 	$(XELATEX) $<


../Output/%.pdf: %.pdf
	mv $< $@

%.pdf: %.tex
	rubber -d  $<





mrproper: clean
	$(RM) *.pdf

clean:
	$(RM) *~ 
	$(RM) *.aux *.log *.toc *.nav *.snm *.out

../Output/notes-cours-systeme.pdf: notes-cours-systeme.tex Style/bouquin.sty

../Output/transparents-cours.pdf: transparents-cours.tex  Style/transparents.sty

