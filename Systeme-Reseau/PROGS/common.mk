CC = gcc
CFLAGS =  -std=c18
CFLAGS += -Wall -Wextra -pedantic -Werror
CFLAGS += -D_XOPEN_SOURCE=700
CFLAGS += -MMD

all: $(execs)

pretty:
	astyle -A3  *.c

clean:
	$(RM) *~ *.orig *.bak *.o *.d

mrproper: clean
	$(RM) $(execs)

-include $(wildcard *.d)

