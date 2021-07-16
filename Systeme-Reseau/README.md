Polycopié "programmation système et réseau en C"

# Répertoires

- `Latex/` : sources Latex du texte
- `PROGS/` : sources C
- `Output/` : PDF

# Vue générale des fichiers

~~~
.
|-- Latex
|   |-- Makefile
|   |-- avant-propos.tex
|   |-- bases-c.tex
|   |-- brouillon.html
|   |-- brouillon.tex
|   |-- documentation.tex
|   |-- fichiers-tuyaux.tex
|   |-- ipc.tex
|   |-- polycop-psr.tex
|   |-- processus.tex
|   |-- resume.tex
|   |-- serveurs-web.tex
|   |-- signaux.tex
|   |-- sockets-locaux.tex
|   |-- tcp-ip.tex
|   `-- test-polycop.tex
|-- Makefile
|-- Output
|   `-- polycop-psr.pdf
|-- PROGS
|   |-- Divers
|   |   |-- Makefile
|   |   |-- avis.c
|   |   |-- biproc.c
|   |   |-- comptage.c
|   |   |-- copie.c
|   |   |-- demon.c
|   |   |-- droits.c
|   |   |-- env.c
|   |   |-- envoifichier.c
|   |   |-- essai-getopt.c
|   |   |-- execl.c
|   |   |-- execv.c
|   |   |-- facture.c
|   |   |-- getlang.c
|   |   |-- getterm.c
|   |   |-- hello.c
|   |   |-- imprimer.c
|   |   |-- inverse.c
|   |   |-- jump.c
|   |   |-- lireligne.c
|   |   |-- mix.c
|   |   |-- numeroter.c
|   |   |-- passfd.c
|   |   |-- redirection.c
|   |   `-- taille.c
|   |-- Echo-Datagrammes
|   |   |-- Makefile
|   |   |-- client-echo.c
|   |   `-- serveur-echo.c
|   |-- Essais
|   |   |-- Makefile
|   |   |-- prenoms.c
|   |   `-- test-waitpid.c
|   |-- IPC
|   |   |-- Makefile
|   |   |-- cons.c
|   |   |-- prod.c
|   |   |-- rcv.c
|   |   |-- sem.c
|   |   `-- snd.c
|   |-- LocalDatagrammes
|   |   |-- Makefile
|   |   |-- client-dgram-local.c
|   |   |-- paire-send.c
|   |   `-- serveur-dgram-local.c
|   |-- LocalStream
|   |   |-- Makefile
|   |   |-- client-stream.c
|   |   |-- serveur-stream-monotache.c
|   |   `-- serveur-stream.c
|   |-- Makefile
|   |-- Resolution
|   |   |-- Makefile
|   |   `-- resolution.c
|   |-- SelectFifo
|   |   |-- Makefile
|   |   `-- lecteur.c
|   |-- Serveurs-Web
|   |   |-- Makefile
|   |   |-- constantes.h
|   |   |-- reseau.c
|   |   |-- reseau.h
|   |   |-- serveur-web-processus.c
|   |   |-- serveur-web-threads.c
|   |   |-- traitement-client.c
|   |   `-- traitement-client.h
|   |-- Signaux
|   |   |-- Makefile
|   |   |-- sig-posix.c
|   |   `-- sig-unix.c
|   |-- TCP-Flots
|   |   |-- Makefile
|   |   `-- client-web.c
|   |-- Threads
|   |   |-- Makefile
|   |   |-- leger.c
|   |   |-- leger_mutex.c
|   |   `-- leger_sem.c
|   |-- common.mk
|   `-- last_check
`-- README.md

15 directories, 88 files
~~~
