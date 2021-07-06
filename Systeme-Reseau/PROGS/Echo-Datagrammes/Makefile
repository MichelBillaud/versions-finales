execs = serveur-echo client-echo

CFLAGS = -std=c11 -Wall -Wextra -pedantic
CFLAGS += -D_XOPEN_SOURCE=700
CFLAGS += -MD

build: $(execs)

serveur-echo: serveur-echo.o
client-echo: client-echo.o
resolution: resolution.o

-include $(wildcard *.d)

pretty:
	astyle -A3  *.c *.h

clean:
	$(RM) *~ *.orig *.bak *.o

mrproper: clean
	$(RM) $(execs) *.d


