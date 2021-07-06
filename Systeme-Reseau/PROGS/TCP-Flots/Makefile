execs = client-web

CFLAGS = -std=c11 -Wall -Wextra -pedantic
CFLAGS += -D_XOPEN_SOURCE=700
CFLAGS += -g

all: $(execs)

pretty:
	astyle -A3  *.c *.h

clean:
	$(RM) *~ *.orig *.bak *.o

mrproper: clean
	$(RM) $(execs)



