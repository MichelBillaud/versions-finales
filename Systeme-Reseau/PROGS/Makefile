FILES = $(shell find . -name *.{c,h})

last_check: $(FILES)
	make compile mrproper
	date > $@

compile:
	for d in */ ; do (cd $$d/; make) ; done


clean:
	$(RM) *~
	for d in */ ; do (cd $$d/; make clean) ; done

mrproper: clean
	for d in */ ; do (cd $$d ; make mrproper) ; done
