execs = serveur-web-processus serveur-web-threads

LDFLAGS = -pthread

include ../common.mk

serveur-web-processus: serveur-web-processus.o reseau.o traitement-client.o
serveur-web-threads: serveur-web-threads.o reseau.o traitement-client.o
