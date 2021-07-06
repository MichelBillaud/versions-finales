PARTIES =  hope.tex preface.tex
PARTIES += chap1-introduction.tex
PARTIES += chap2-programmer-avec-des-fonctions.tex
PARTIES += chap3-induction-recursion.tex
PARTIES += chap4-listes.tex chap5-arbres.tex chap6-semantique.tex
PARTIES += conclusion.tex

PICS = pic_abr.tex pic_arbin.tex pic_arbres.tex
PICS += pic_max3.tex pic_patate.tex pic_signe.tex

hope.pdf: $(PARTIES) $(addprefix Pictures/, $(PICS))
	xelatex hope

again: hope.pdf
	xelatex hope

# rubber -d hope


clean:
	$(RM) *~ *.aux *.toc *.log *.fls *.bbl *.bib *.blg

