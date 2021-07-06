/*
  LocalStream/serveur-stream-monotache.c

  Envoi/réception de données par un socket local (mode connecté)

  Exemple de serveur monotâche qui gère plusieurs connexions

  - attend une connexion
  - lit du texte
  - envoie une réponse
 */


#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <sys/select.h>
#include <stdbool.h>


#define TAILLE_TAMPON             1000
#define MAX_CONNEXIONS_EN_ATTENTE 4
#define MAX_CLIENTS               10

/* les données propres à chaque client */

#define INACTIF -1
struct {
    int fd;
    int numero_connexion;
    int compteur;
} client[MAX_CLIENTS];

void abandon(char message[])
{
    perror(message);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    size_t taille_adresse;
    int nb_connexions = 0;

    /* 1. réception des paramètres de la ligne de commande */

    if (argc != 2) {
        printf("usage: %s chemin\n", argv[0]);
        abandon("mauvais nombre de paramètres");
    }
    char * chemin = argv[1];

    /* 3. Initialisation du socket de réception */
    /* 3.1 création du socket   */
    struct sockaddr_un adresse;
    int fd_serveur = socket(PF_LOCAL, SOCK_STREAM, 0);
    if (fd_serveur < 0) {
        abandon("Création du socket serveur");
    }

    /* 3.2 Remplissage adresse serveur */
    adresse.sun_family = AF_LOCAL;
    strcpy(adresse.sun_path, chemin);
    taille_adresse = sizeof adresse;

    /* 3.3 Association de l'adresse au socket */
    taille_adresse = sizeof adresse;
    if (bind(fd_serveur,
             (struct sockaddr *) &adresse, taille_adresse) < 0) {
        abandon("bind");
    }

    /* 3.4 Ce socket attend des connexions mises en file d'attente */
    listen(fd_serveur, MAX_CONNEXIONS_EN_ATTENTE);

    printf("SERVEUR> Le serveur écoute le socket %s\n", chemin);

    /* 3.5 initialisation du tableau des clients */
    for (int i = 0; i < MAX_CLIENTS; i++) {
        client[i].fd = INACTIF;
    }

    /* 4. boucle du serveur */

    while(true) {
        /* 4.1 remplissage des masques du select */
        fd_set fds_lecture;
        FD_ZERO(&fds_lecture);
        // serveur (pour nouvelles connexions)
        FD_SET(fd_serveur, &fds_lecture);
        // clients actifs
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (client[i].fd != INACTIF)
                FD_SET(client[i].fd, &fds_lecture);
        }

        /* 4.2 attente d'un événement (ou plusieurs) */
        int nb_fds_prets = select(FD_SETSIZE,
                                  &fds_lecture, NULL, NULL,
                                  NULL);
        assert(nb_fds_prets >= 0);

        /* 4.3 en cas de nouvelle connexion : */
        if (FD_ISSET(fd_serveur, &fds_lecture)) {
            /* si il y a de la place dans la table des clients,
               on y ajoute la nouvelle connexion */
            nb_fds_prets--;
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (client[i].fd == INACTIF) {
                    int fd_client = accept(fd_serveur, NULL, NULL);
                    if (fd_client < 0)
                        abandon("accept");
                    nb_connexions++;
                    client[i].fd = fd_client;
                    client[i].numero_connexion = nb_connexions;
                    client[i].compteur = 0;
                    printf("SERVEUR> arrivée de connexion #%d (fd %d)\n",
                           client[i].numero_connexion, fd_client);
                    break;
                }
                if (i >= MAX_CLIENTS) {
                    printf("SERVEUR> trop de connexions !\n");
                }
            }
        };

        /* 4.4 traitement des clients actifs qui ont reçu des données */
        for (int i = 0; (i < MAX_CLIENTS) && (nb_fds_prets > 0); i++) {
            if ((client[i].fd != INACTIF) &&
                    FD_ISSET(client[i].fd, &fds_lecture)) {
                nb_fds_prets--;
                char tampon[TAILLE_TAMPON];
                int nb_octets_lus = read(client[i].fd, tampon,
                                         TAILLE_TAMPON - 1);
                printf("SERVEUR> données reçues de #%d (%d octets)\n",
                       client[i].numero_connexion, nb_octets_lus);
                if (nb_octets_lus > 0)
                    client[i].compteur += nb_octets_lus;
                else {
                    printf("SERVEUR> envoi de la réponse au client #%d.\n",
                           client[i].numero_connexion);
                    int taille_reponse =
                        sprintf(tampon,
                                "*** Fin de la connexion #%d\n"
                                "*** Vous m'avez envoyé %d caractères\n"
                                "*** Merci et à bientôt.\n",
                                client[i].numero_connexion,
                                client[i].compteur);
                    write(client[i].fd, tampon, taille_reponse);
                    close(client[i].fd);
                    /* enlèvement de la liste des clients */
                    client[i].fd = INACTIF;
                }
            }
        }
    }
    /* on ne passe jamais ici (boucle sans fin) */
    return EXIT_SUCCESS;
}
