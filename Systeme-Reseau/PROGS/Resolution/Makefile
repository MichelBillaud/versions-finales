execs = resolution

CFLAGS = -std=c18 -D_XOPEN_SOURCE=700
CFLAGS += -Wall -Wextra -pedantic
CFLAGS += -g
CFLAGS +=  -MMD

build: $(execs)

resolution: resolution.o

-include $(wildcard *.d)

pretty:
	astyle -A3  *.c *.h

clean:
	$(RM) *~ *.orig *.bak *.o *.d

mrproper: clean
	$(RM) $(execs)


