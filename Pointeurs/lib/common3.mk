HTMLCSS = ../lib/html.css
EPUB_CSS = ../lib/epub.css

SRC = $(wildcard *.md)

HTML      = $(addprefix $(HTMLDIR)/,$(addsuffix .html,$(HTMLPAGES)))

PDF += $(addprefix $(PDFDIR)/,$(addsuffix .pdf,$(PDF1COL)))
PDF += $(addprefix $(PDFDIR)/,$(addsuffix .2col.pdf,$(PDF2COLS)))
PDF += $(addprefix $(SLIDESDIR)/,$(addsuffix .pdf,$(PDFSLIDES)))

EPUBFILES = $(addprefix $(EBOOKSDIR)/,$(addsuffix .epub,$(EBOOKS)))

PANDOC_PDF = pandoc -t latex --pdf-engine=xelatex -N --toc --self-contained -V lang=fr  -V fontfamily=bookman -V papersize:a4wide -V geometry:left=3cm,right=3cm,top=2cm,bottom=2cm -V documentclass:extarticle

PANDOC_TWOCOL_PDF = $(PANDOC_PDF)  -V classoption:twocolumn

PANDOC_HTML = pandoc  -N --toc -t html5  -c $(HTMLCSS) --self-contained

PANDOC_SLIDES_PDF = pandoc  --pdf-engine=xelatex -t beamer -N --toc -V theme:Boadilla -V colortheme:crane  

PANDOC_EPUB = pandoc --toc --standalone -N -V lang=fr --metadata=lang:"fr-FR"  --css $(EPUB_CSS) --top-level-division=chapter


all: $(PDF) $(HTML) $(EPUBFILES)

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

$(SLIDESDIR)/%.pdf: %.md
	$(PANDOC_SLIDES_PDF) -o $@ $^

$(EBOOKSDIR)/%.epub: %.meta %.md
	$(PANDOC_EPUB) -o $@  $^

$(EBOOKSDIR)/%.epub:  %.md
	$(PANDOC_EPUB) -o $@  $^

clean:
	$(RM) *~


