LANG=C

#
# Makefile pour le polycop Systeme et Reseau
#

src_dir = ../PROGS
dst_dir = tmp


pubdir = billaud@ssh1.labri.fr:SITE-PERSO-LABRI/travaux/SYSRESEAU

all: polycop-psr.pdf  # test-polycop.pdf



parties = polycop-psr.tex avant-propos.tex
parties += bases-c.tex ipc.tex tcp-ip.tex
parties += fichiers-tuyaux.tex resume.tex serveurs-web.tex
parties += signaux.tex processus.tex sockets-locaux.tex documentation.tex

sources += $(src_dir)/Divers/envoifichier.c
sources += $(src_dir)/Divers/imprimer.c
sources += $(src_dir)/Divers/hello.c
sources += $(src_dir)/Divers/env.c
sources += $(src_dir)/Divers/essai-getopt.c
sources += $(src_dir)/Divers/getterm.c
sources += $(src_dir)/Divers/droits.c
sources += $(src_dir)/Divers/jump.c
sources += $(src_dir)/Divers/lireligne.c
sources += $(src_dir)/Divers/facture.c
sources += $(src_dir)/Divers/comptage.c
sources += $(src_dir)/Divers/copie.c
sources += $(src_dir)/Divers/taille.c
sources += $(src_dir)/Divers/redirection.c
sources += $(src_dir)/Divers/avis.c
sources += $(src_dir)/Divers/mix.c
sources += $(src_dir)/Divers/inverse.c
sources += $(src_dir)/SelectFifo/lecteur.c
sources += $(src_dir)/LocalDatagrammes/serveur-dgram-local.c
sources += $(src_dir)/LocalDatagrammes/client-dgram-local.c
sources += $(src_dir)/LocalStream/client-stream.c
sources += $(src_dir)/LocalStream/serveur-stream.c
sources += $(src_dir)/LocalStream/serveur-stream-monotache.c
sources += $(src_dir)/LocalDatagrammes/paire-send.c
sources += $(src_dir)/Divers/biproc.c
sources += $(src_dir)/Divers/execv.c
sources += $(src_dir)/Divers/execl.c
sources += $(src_dir)/Divers/demon.c
sources += $(src_dir)/Signaux/sig-unix.c
sources += $(src_dir)/Signaux/sig-posix.c
sources += $(src_dir)/Threads/leger_mutex.c
sources += $(src_dir)/IPC/prod.c
sources += $(src_dir)/IPC/cons.c
sources += $(src_dir)/IPC/sem.c
sources += $(src_dir)/IPC/snd.c
sources += $(src_dir)/IPC/rcv.c
sources += $(src_dir)/Echo-Datagrammes/client-echo.c
sources += $(src_dir)/Echo-Datagrammes/serveur-echo.c
sources += $(src_dir)/TCP-Flots/client-web.c
sources += $(src_dir)/Serveurs-Web/serveur-web-processus.c
sources += $(src_dir)/Serveurs-Web/serveur-web-threads.c
sources += $(src_dir)/Serveurs-Web/reseau.c
sources += $(src_dir)/Serveurs-Web/reseau.h
sources += $(src_dir)/Serveurs-Web/traitement-client.c
sources += $(src_dir)/Serveurs-Web/traitement-client.h
sources += $(src_dir)/Divers/passfd.c

polycop-psr.pdf: polycop-psr.tex ${parties} $(sources)
	rubber  -d $< 


pretty:
	for f in ${sources} ; do astyle -A3 $$f ; done

clean:
	$(RM) *~ *.aux *.idx *.ilg *.ind *.log *.out *.toc
	(cd $(src_dir) ; make clean)

mrproper: clean
	$(RM) polycop-psr.pdf 

mount:
	ssh billaud@ssh2.labri.fr montage-web.sh

publish: polycop-psr.pdf clean
	rsync -avz --exclude .svn --delete . $(pubdir)





