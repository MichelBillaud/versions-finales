execs = client-dgram-local paire-send serveur-dgram-local

CFLAGS = -std=c18 -Wall -Wextra -pedantic
CFLAGS += -D_XOPEN_SOURCE=700
CFLAGS += -MMD

all: $(execs)



pretty:
	astyle -A3   *.c 

clean:
	$(RM) *~ *.orig *.bak *.o

mrproper: clean
	$(RM) $(execs)

-include $(wildcard *.d)

