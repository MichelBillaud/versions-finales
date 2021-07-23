ALL =  notes-de-cours-langages.pdf 
ALL += imprimable.pdf
# ALL livret.pdf 
ALL += exercices-rationnels.pdf devoir.pdf
ALL += complements.pdf
ALL += td-grammaires.pdf
ALL += devoir.pdf devoir-rattrappage.pdf

PDF =  $(addprefix ../Output/, $(ALL))

PDF += ../Output/notes-de-cours-langages.pdf

../Output/%.pdf: %.tex
	xelatex -output-directory ../Output $<
	xelatex -output-directory ../Output $<


all: $(PDF)

../Output/notes-de-cours-langages.pdf:  notes-de-cours-langages.tex ../src/*.cc ../src/*.cxx  ../src/*.h bnf.tex ../src/Makefile


# livret-langages.pdf : livret-langages.tex langages-algebriques.tex langages-rationnels.tex motivations.tex

../Output/complements.pdf: complements.tex bnf.tex

../Output/imprimable.pdf:  ../Output/notes-de-cours-langages.pdf
	pdfnup --nup 2x1 --landscape --twoside -o $@ $^

../Output/livret.pdf:  livret.tex ../Output/notes-de-cours-langages.pdf


clean:
	$(RM) *~
