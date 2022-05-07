all: cours-c.pdf

%.pdf: %.tex
	rubber -d $<


cours-c.pdf: cours-c.tex ../Sim16/sim16.c

clean: 
	$(RM) *.aux  *.log  *.out  *.toc *.bak *~

