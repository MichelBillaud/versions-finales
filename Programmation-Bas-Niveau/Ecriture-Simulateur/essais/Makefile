CFLAGS =-std=c17 -Wall -pedantic
CFLAGS += -MMD

execs   = hex lecture bits

all : $(execs)


pretty:
	astyle -A4 *.c *.h 2>/dev/null

clean:
	$(RM) *.o *~ *.orig *.bak *.d


mrproper: clean
	$(RM) $(execs)

-include $(wildcard *.d)

