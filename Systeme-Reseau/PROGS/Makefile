clean:
	$(RM) *~
	for d in */ ; do (cd $$d/; make clean) ; done

mrproper: clean
	for d in `grep -l mrproper */Makefile | xargs dirname` ; do (cd $$d ; make mrproper) ; done
