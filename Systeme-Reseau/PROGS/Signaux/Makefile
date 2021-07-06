execs = sig-unix sig-posix 

CFLAGS = -std=c18 -Wall -Wextra -pedantic
CFLAGS += -g
CFLAGS += -D_XOPEN_SOURCE=700
CFLAGS += -MMD

build: $(execs)


sig-unix: sig-unix.o
sig-posix: sig-posix.o

-include $(wildcard *.d)

pretty:
	astyle -A3  *.c 

clean:
	$(RM) *~ *.orig *.bak *.o *.d

mrproper: clean
	$(RM) $(execs)


