pdf = ecrire-simulateur-v3.pdf
# pdf += ecrire-simulateur-v1.pdf
pdf += slides-ecriture-simulateur.pdf 

all: $(pdf)

%.pdf: %.tex
	rubber -d $<


clean:
	$(RM) *~ *.aux *.log *.nav *.out *.snm *.toc 
