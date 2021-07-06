/* LocalDatagrammes/serveur-dgram-local.c */

/*
   Usage:  serveur-dgram-local chemin

   Reçoit des datagrammes par un socket du domain local,
   et les affiche. Le paramètre indique le nom du socket.
   S'arrête quand la donnée est "stop".
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdbool.h>

#define TAILLE_MAX_DONNEE 1024

void abandon(char message[]);
int ouvrir_socket_reception(const char *chemin);


int main (int argc, char * argv[])
{
    if (argc != 2) {
        fprintf(stderr,"usage: %s chemin\n", argv[0]);
        abandon("mauvais nombre de parametres");
    }

    int fd = ouvrir_socket_reception(argv[1]);

    printf("> Serveur démarré sur socket local \"%s\"\n", argv[1]);
    while (true) {
        char tampon[TAILLE_MAX_DONNEE + 1]; // +1 pour ajouter terminateur
        int nb_octets_recus
            = recvfrom(fd, tampon, TAILLE_MAX_DONNEE, 0, NULL, NULL);
        if (nb_octets_recus <= 0) {
            abandon("Réception datagramme");
        }
        tampon[nb_octets_recus] = '\0'; // ajout terminateur
        printf("Reçu : %s\n", tampon);
        if (strcmp(tampon, "stop") == 0) {
            printf("> arrêt demandé\n");
            break;
        }
    }
    close(fd);
    return EXIT_SUCCESS;
}


int ouvrir_socket_reception(const char *chemin)
{
    // construction de l'adresse
    struct sockaddr_un  adresse;
    adresse.sun_family  = AF_LOCAL;
    strcpy(adresse.sun_path, chemin);

    // construction du socket de réception
    int fd = socket(PF_LOCAL, SOCK_DGRAM, 0);
    if (fd < 0) {
        abandon("Création du socket serveur");
    }

    // association socket/adresse
    socklen_t longueur_adresse  = sizeof adresse;
    if (bind(fd, (struct sockaddr *) &adresse, longueur_adresse) < 0) {
        abandon("Nommage du socket serveur");
    }
    return fd;
}

void abandon(char message[])
{
    perror(message);
    exit(EXIT_FAILURE);
}
