execs = serveur-web-processus serveur-web-threads

CFLAGS = -std=c18 -Wall -Wextra -pedantic -Werror
CFLAGS += -pthread
CFLAGS += -D_XOPEN_SOURCE=700
CFLAGS += -g
CFLAGS += -MMD

LDFLAGS = -pthread


all: $(execs)

serveur-web-processus: serveur-web-processus.o reseau.o traitement-client.o

serveur-web-threads: serveur-web-threads.o reseau.o traitement-client.o

pretty:
	astyle -A3  *.c *.h

clean:
	$(RM) *~ *.orig *.bak *.o *.d

mrproper: clean
	$(RM) $(execs)

-include $(wildcard *.d)
