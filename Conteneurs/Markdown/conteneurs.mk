#
# Dépendances 
#

HTMLPAGES += conteneurs
EBOOKS += conteneurs
PDF1COL += conteneurs

PARTS = conteneurs.md
PARTS +=	part-introduction.md
PARTS +=	part-rappels.md
PARTS +=	chap-rappels.md
PARTS +=	chap-pointeurs.md
PARTS +=	chap-allocation.md
PARTS +=	part-conteneurs.md
PARTS +=	chap-tableaux-extensibles.md
PARTS +=	chap-ensemble-chaines.md

$(HTMLDIR)/conteneurs.html \
$(EBOOKSDIR)/conteneurs.epub \
$(PDFDIR)/conteneurs.pdf : conteneurs.meta $(PARTS)


