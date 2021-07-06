execs = cons prod rcv sem snd


CFLAGS = -std=c11 -Wall -Wextra -pedantic
CFLAGS +=  -D_XOPEN_SOURCE=700

all: $(execs)


pretty:
	astyle -A3  *.c *.h

clean:
	$(RM) *~ *.orig *.bak *.o

mrproper: clean
	$(RM) $(execs)

# DO NOT DELETE
