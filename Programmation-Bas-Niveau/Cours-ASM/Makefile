DOCS = cours-asm slides-asm feuille questions

all: $(addsuffix, .pdf, $(DOCS))



%.pdf: %.tex
	rubber -d $<

clean:
	$(RM) *~
	for d in $(DOCS) ; do rubber --clean $$d; done


slides-asm.pdf:  01-intro.tex 03-programmation.tex 02-processeur.tex 
cours-asm.pdf: cours-asm.tex

%.d: %.tex
	grep lstinputlisting $< | sed -e  "s/^.*{/`basename $< .tex`.pdf: /" -e  "s/}.*\$$// " > $@
	grep inputgraphics $< | sed -e  "s/^.*{/`basename $< .tex`.pdf: /" -e  "s/}.*\$$// " >> $@

-include $(addsuffix .d,$(DOCS))



