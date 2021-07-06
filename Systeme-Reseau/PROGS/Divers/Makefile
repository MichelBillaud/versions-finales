CC = gcc
CFLAGS =  -std=c18
CFLAGS += -Wall -Wextra -pedantic -Werror
CFLAGS += -D_XOPEN_SOURCE=700
CFLAGS += -MMD

sources = $(wildcard *.c)

modules = demon.c
progs = $(filter-out $(modules),$(sources))

execs = $(progs:.c=)

all: $(execs)

pretty:
	astyle -A3  *.c

clean:
	$(RM) *~ *.orig *.bak *.o *.d

mrproper: clean
	$(RM) $(execs)

# DO NOT DELETE
-include $(wildcard *.d)

