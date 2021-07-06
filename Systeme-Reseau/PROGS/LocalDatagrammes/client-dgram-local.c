/* LocalDatagrammes/client-dgram-local.c */

/*
   Usage:  client-dgram-local chemin messages

   Envoie des datagrammes à un socket du domain local,
   et les affiche. Le premier paramètre indique le nom du socket,
   les autres des chaînes de caractères.

   Exemple : client-dgram-local un deux "trente et un" stop
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

#define TAILLE_MAX_DONNEE 1024

void abandon(char message[]);

int main (int argc, char * argv[])
{
    if (argc <= 2) {
        fprintf(stderr,"usage: %s chemin message\n", argv[0]);
        abandon("mauvais nombre de paramètres");
    }

    struct sockaddr_un  adresse;
    adresse.sun_family      = AF_LOCAL;
    strcpy(adresse.sun_path,argv[1]);
    int longueur_adresse        = sizeof adresse; // SUN_LEN (&adresse);

    int fd = socket(PF_LOCAL,SOCK_DGRAM,0);
    if (fd < 0) {
        abandon("Création du socket client");
    }

    for (int k = 2; k < argc; k++) {
        // limitation
        int nb_octets = strlen(argv[k]);
        if (nb_octets > TAILLE_MAX_DONNEE) {
            nb_octets = TAILLE_MAX_DONNEE;
        }

        /* le message est envoyé sans le terminateur '\0' */
        if ( sendto(fd, argv[k], nb_octets, 0,
                    (struct sockaddr *) &adresse,
                    longueur_adresse) < 0) {
            abandon("Expédition du message");
        }
        printf(".");
        fflush(stdout);
        sleep(1);
    }

    printf("OK\n");
    close(fd);
    return EXIT_SUCCESS;
}

void abandon(char message[])
{
    perror(message);
    exit(EXIT_FAILURE);
}
