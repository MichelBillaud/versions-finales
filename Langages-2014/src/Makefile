ALL =  notes-de-cours-langages.pdf 
ALL += imprimable.pdf  livret.pdf 
ALL += exercices-rationnels.pdf devoir.pdf
# ALL += complements.pdf
ALL += td-grammaires.pdf
ALL += devoir.pdf devoir-rattrappage.pdf

all: $(ALL)

%.pdf: %.tex
	rubber -f -d $<


# livret-langages.pdf : livret-langages.tex langages-algebriques.tex langages-rationnels.tex motivations.tex

complements.pdf: complements.tex bnf.tex

imprimable.pdf:  notes-de-cours-langages.pdf
	pdfnup --nup 2x1 --landscape --twoside -o $@ $^

livret.pdf:  livret.tex notes-de-cours-langages.pdf

notes-de-cours-langages.pdf: src/*.cc src/*.cxx  src/*.h bnf.tex src/Makefile

clean:
	for f in $(ALL) ; do rubber --clean $$(basename $$f .pdf ) ; done