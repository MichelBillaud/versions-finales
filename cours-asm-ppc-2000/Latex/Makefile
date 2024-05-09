
OUTPUT_DIR =  ../Output

all : $(OUTPUT_DIR)/cours-asm-ppc.pdf

$(OUTPUT_DIR)/%.pdf: %.tex
	rubber $<
	cp *.pdf $@

clean:
	$(RM) *~
	rubber --clean *.tex

mrproper: clean
	$(RM) $(OUTPUT_DIR)/*
