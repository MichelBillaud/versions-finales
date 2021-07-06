/*
  LocalStream/serveur-stream.c

  Envoi/réception de données par un socket local (mode connecté)

  Exemple de serveur qui
  - attend une connexion
  - lit du texte
  - envoie une réponse

  Remarques
  - ce serveur ne traite qu'une connexion à la fois.
  - Il ne s'arrête jamais.
 */


#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define TAILLE_TAMPON             1000
#define MAX_CONNEXIONS_EN_ATTENTE 4


void dialoguer_avec_client(int fd_client, int numero_client);


int main(int argc, char *argv[])
{
    int numero_connexion = 0;

    /* 1. réception des paramètres de la ligne de commande */

    if (argc != 2) {
        printf("usage: %s chemin\n", argv[0]);
        return EXIT_FAILURE;
    }
    char * chemin = argv[1];

    /* 3. Initialisation du socket de réception */
    /* 3.1 création du socket   */
    int fd_serveur = socket(PF_LOCAL, SOCK_STREAM, 0);
    assert (fd_serveur >= 0);

    /* 3.2 Remplissage adresse serveur */
    struct sockaddr_un adresse;
    adresse.sun_family = AF_LOCAL;
    strcpy(adresse.sun_path, chemin);
    size_t taille_adresse = sizeof adresse;

    /* 3.3 Association de l'adresse au socket */
    assert (bind(fd_serveur,
                 (struct sockaddr *) &adresse, taille_adresse) >= 0);


    /* 3.4 Ce socket attend des connexions mises en file d'attente */
    listen(fd_serveur, MAX_CONNEXIONS_EN_ATTENTE);

    printf("SERVEUR> Le serveur écoute le socket %s\n", chemin);

    /* 4. boucle du serveur */
    for (;;) {
        /* 4.1 attente d'une connexion */
        printf("SERVEUR> Attente d'une connexion.\n");
        int fd_client = accept(fd_serveur, NULL, NULL);
        assert (fd_client > 0);

        numero_connexion++;
        printf("SERVEUR> Connexion #%d établie.\n", numero_connexion);

        dialoguer_avec_client(fd_client, numero_connexion);

        /* 4.3 fermeture de la connexion */
        close(fd_client);

    }

    /* on ne passe jamais ici */
    return EXIT_SUCCESS;
}

void dialoguer_avec_client(int fd_client, int numero_client)
{
    int compteur = 0;
    while(true) {
        char tampon_lecture[TAILLE_TAMPON];

        int nb_octets_lus
            = read(fd_client, tampon_lecture, TAILLE_TAMPON - 1);
        if (nb_octets_lus <= 0) {
            break;
        }
        compteur += nb_octets_lus;
        tampon_lecture[nb_octets_lus] = '\0';
        printf("%s", tampon_lecture);
    }

    /* 4.4 plus de données, on envoit une réponse */
    printf("SERVEUR> envoi de la réponse.\n");

    char tampon_reponse[TAILLE_TAMPON];
    int taille_reponse
        = sprintf(tampon_reponse,
                  "*** Fin de la connexion au client #%d\n"
                  "*** Vous m'avez envoyé %d caractères\n"
                  "*** Merci et à bientot.\n",
                  numero_client, compteur);
    write(fd_client, tampon_reponse, taille_reponse);
    printf("SERVEUR> fin de connexion.\n");
}

