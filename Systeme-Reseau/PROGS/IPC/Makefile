execs = cons prod rcv sem snd


CFLAGS = -std=c18 -Wall -Wextra -pedantic
CFLAGS +=  -D_XOPEN_SOURCE=700
CFLAGS += -MMD

all: $(execs)


pretty:
	astyle -A3  *.c *.h

clean:
	$(RM) *~ *.orig *.bak *.o *.d

mrproper: clean
	$(RM) $(execs)

-include $(wildcard *.d)
