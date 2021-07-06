/*
  Projet serveurs Web - reseau.c
  Fonctions réseau
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/errno.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <signal.h>
#include <netdb.h>


#include "reseau.h"

/**
 *  démarre un service TCP sur le port indiqué
 */

int ouvrir_serveur_tcp(const char port[])
{
    struct addrinfo *adr_premier;
    struct addrinfo indications = {
        .ai_family = AF_INET6,
        .ai_flags = AI_PASSIVE
        };
    int r = getaddrinfo(NULL, port, &indications, &adr_premier);
    if (r != 0) {
        perror("resolution nom de service");
        exit(EXIT_FAILURE);
    }
    int fd = -1;

    for (struct addrinfo * ptr = adr_premier; ptr != NULL; ptr = ptr->ai_next) {
        fd = socket(ptr->ai_family, SOCK_STREAM, 0);
        if (fd < 0) {
            continue;
        }
        r = bind(fd, ptr->ai_addr, ptr->ai_addrlen);
        if (r < 0) {
                close(fd);
                fd = -1;
            } else {
                break; // on a trouvé un socket qui marche .
            }
        }
        freeaddrinfo(adr_premier);
        listen(fd, 4);
        return fd;
    }

    /**
     * retourne le file-descriptor du prochain
     * client connecté sur le serveur
     */
    int ouvrir_client(int fd_serveur)
    {
        /* A cause des signaux SIGCHLD, la fonction accept()
           peut être interrompue quand un fils se termine.
           Dans ce cas, on relance accept().
         */
        while (true) {
            int fd_client = accept(fd_serveur, NULL, NULL);
            if (fd_client > 0) {
                return fd_client;
            }
            if (errno != EINTR) {
                perror("attente client");
                exit(EXIT_FAILURE);
            };
        };
    }

