OUTDIR = ../Output

MAINS = circuits-logiques

PDF = $(addsuffix .pdf, $(addprefix $(OUTDIR)/, $(MAINS)))

# PDF = $(OUTDIR)/circuits-logiques.pdf

SRC=circuits-logiques.tex abrev.tex elements.tex codages.tex techno.tex \
	 boole.tex sequ.tex combi.tex
EPS=fig1.eps fig2.eps fig3.eps fig4.eps fig5.eps fig6.eps fig7.eps \
	fig8.eps fig9.eps fig10.eps  boole1.eps boole2.eps boole3.eps \
	seq1.eps seq2.eps seq3.eps seq4.eps seq5.eps \
	combi1.eps combi2.eps combi3.eps combi4.eps combi5.eps \
	combi6.eps combi7.eps combi8.eps 

IMG = $(addprefix ../Images/, $(EPS))

all:	$(PDF)

%.pdf: %.tex
	rubber -d $<


$(OUTDIR)/%.pdf: %.pdf
	mv $< $@

# dépendances

$(OUTDIR)/circuits-logiques.pdf: $(SRC) $(IMG)


clean:
	$(RM) *~
	for d in $(MAINS); do rubber --clean $$d ; done




