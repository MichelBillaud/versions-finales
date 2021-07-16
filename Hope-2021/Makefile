SRCDIR = Sources
PICDIR = Pictures
OUTPUTDIR = Output

SRC =  hope.tex preface.tex
SRC += chap1-introduction.tex
SRC += chap2-programmer-avec-des-fonctions.tex
SRC += chap3-induction-recursion.tex
SRC += chap4-listes.tex chap5-arbres.tex chap6-semantique.tex
SRC += conclusion.tex

PICS = pic_abr.tex pic_arbin.tex pic_arbres.tex
PICS += pic_max3.tex pic_patate.tex pic_signe.tex

INPUTS = /usr/local/share/texmf:Sources:Pictures:

CMD = TEXINPUTS=$(INPUTS)  xelatex -output-directory $(OUTPUTDIR) hope

$(OUTPUTDIR)/hope.pdf: $(wildcard */*.tex)
	$(CMD) ; $(CMD) 


# rubber -d hope


clean:
	$(RM) */*.aux */*.toc */*.log */*.fls */*.bbl */*.bib */*.blg */\#*



