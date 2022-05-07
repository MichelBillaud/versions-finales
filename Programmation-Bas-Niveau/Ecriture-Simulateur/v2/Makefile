CFLAGS = -std=c17 -Wall -pedantic
CFLAGS += -MMD

objets = simulateur.o entrees-sorties.o execution.o
exec   = simulateur

$(exec): $(objets)

pretty:
	astyle -A4 *.c *.h 2>/dev/null

clean:
	$(RM) *.o *~ *.orig *.bak *.d

mrproper: clean
	$(RM) $(exec) 

-include $(wildcard *.d)
