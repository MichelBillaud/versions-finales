CFLAGS=-std=c11 -Wall -Wextra -g
CFLAGS += -MMD

mains =  com16 com16-stack

all: $(mains)

pretty:
	astyle -s2 $(wildcard *.c *.h)

clean:
	$(RM)  *~ *.orig *.o *.d

mrproper: clean
	$(RM) $(mains)

-include $(wildcard *.d)


