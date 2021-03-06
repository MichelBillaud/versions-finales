HTMLCSS = ../lib/html.css
EPUB_CSS = ../lib/epub.css


HTMLFILES      = $(addprefix $(HTMLDIR)/,$(addsuffix .html,$(HTMLPAGES)))

PDFFILES += $(addprefix $(PDFDIR)/,$(addsuffix .pdf,$(PDF1COL)))
PDFFILES += $(addprefix $(PDFDIR)/,$(addsuffix .2col.pdf,$(PDF2COLS)))
PDFFILES += $(addprefix $(PDFDIR)/,$(addsuffix .pdf,$(LATEXPDF)))

SLIDESFILES = $(addprefix $(SLIDESDIR)/,$(addsuffix .pdf,$(PDFSLIDES)))
EPUBFILES   = $(addprefix $(EBOOKSDIR)/,$(addsuffix .epub,$(EBOOKS)))

# ENGINE = --pdf-engine=xelatex

PANDOC_PDF = pandoc -t latex  -N --toc $(ENGINE) --self-contained -V lang=fr --variable=geometry:a4paper,inner=1.5cm,outer=1cm,tmargin=2cm,bmargin=3cm  -V documentclass:extarticle

PANDOC_TWOCOL_PDF = $(PANDOC_PDF)  -V classoption:twocolumn

PANDOC_HTML = pandoc  -N --toc -t html5  -c $(HTMLCSS) --self-contained

PANDOC_SLIDES_PDF = pandoc  --pdf-engine=xelatex -t beamer -N --toc -V theme:Boadilla -V colortheme:crane  

PANDOC_EPUB = pandoc --toc --standalone -N -V lang=fr --metadata=lang:"fr-FR"  --css $(EPUB_CSS) --top-level-division=chapter

LATEX_PDF = xelatex -halt-on-error -output-directory $(PDFDIR) $<


all: all_files




$(HTMLDIR)/%.html: %.meta %.md 
	$(PANDOC_HTML)	  $^  -o $@

$(HTMLDIR)/%.html: %.md 
	$(PANDOC_HTML)	  $^  -o $@


$(PDFDIR)/%.2col.pdf: %.md
	$(PANDOC_TWOCOL_PDF) -o $@ $^

$(PDFDIR)/%.pdf: %.meta %.md
	$(PANDOC_PDF) -o $@ $^

$(PDFDIR)/%.pdf: %.md
	$(PANDOC_PDF) -o $@ $^

$(PDFDIR)/%.pdf: %.tex
	$(LATEX_PDF) $<

$(SLIDESDIR)/%.pdf: %.meta %.md
	$(PANDOC_SLIDES_PDF) -o $@ $^

$(SLIDESDIR)/%.pdf: %.md
	$(PANDOC_SLIDES_PDF) -o $@ $^

$(EBOOKSDIR)/%.epub: %.meta %.md
	$(PANDOC_EPUB) -o $@  $^

$(EBOOKSDIR)/%.epub: %.md
	$(PANDOC_EPUB) -o $@  $^

clean:
	$(RM) *~
	$(RM) $(PDFDIR)/*.aux $(PDFDIR)/*.log


-include $(wildcard *.mk)

all_files : $(PDFFILES) $(HTMLFILES) $(EPUBFILES) $(SLIDESFILES)

