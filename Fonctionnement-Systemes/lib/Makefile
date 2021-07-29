HTMLDIR = ../HTML-PUBLIC

include ../lib/common2.mk



publish: all
	rsync -av --delete  $(HTMLDIR)/* ~/sites/labri/notes


