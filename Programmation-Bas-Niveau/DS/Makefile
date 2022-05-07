%.pdf: %.tex
	rubber --warn=all --verbose $<

ds.pdf: ds.tex asm.tex cours.tex c.tex  main.tex

all: ds.pdf

clean:
	$(RM) *.log *.aux 

