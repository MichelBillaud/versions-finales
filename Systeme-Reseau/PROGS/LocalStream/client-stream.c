/*
  LocalStream/client-stream.c

  Envoi/réception de données par un socket local (mode connecté)

  Exemple de client qui
  - ouvre un socket
  - envoie sur ce socket du texte lu sur l'entree standard
  - attend et affiche une réponse
  */

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define TAILLE_TAMPON 1000

void abandon(char message[])
{
    perror(message);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    char *chemin;		/* chemin d'accès du socket serveur */
    socklen_t longueur_adresse;
    struct sockaddr_un adresse;
    int fd;

    /* 1. réception des paramètres de la ligne de commande */
    if (argc != 2) {
        printf("Usage: %s chemin\n", argv[0]);
        abandon("Mauvais nombre de paramètres");
    }
    chemin = argv[1];

    /* 2. Initialisation du socket */

    /* 2.1 création du socket   */
    fd = socket(PF_LOCAL, SOCK_STREAM, 0);
    if (fd < 0)
        abandon("Création du socket client");

    /* 2.2 Remplissage adresse serveur */
    adresse.sun_family = AF_LOCAL;
    strcpy(adresse.sun_path, chemin);
    longueur_adresse = sizeof adresse;

    /* 2.3 connexion au serveur */
    if (connect(fd, (struct sockaddr *) &adresse, longueur_adresse)
            < 0)
        abandon("connect");

    printf("CLIENT> Connexion établie\n");

    /* 3. Lecture et envoi des données */
    for (;;) {
        char tampon[TAILLE_TAMPON];
        int nb_lus, nb_envoyes;

        nb_lus = read(0, tampon, TAILLE_TAMPON);
        if (nb_lus <= 0)
            break;
        nb_envoyes = write(fd, tampon, nb_lus);
        assert (nb_envoyes == nb_lus);
    }
    /* 4. Fin de l'envoi */
    shutdown(fd, SHUT_WR);
    printf("CLIENT> Fin envoi, attente de la réponse.\n");

    /* 5. Réception et affichage de la réponse */
    for (;;) {
        char tampon[TAILLE_TAMPON];
        int nb_lus;
        nb_lus = read(fd, tampon, TAILLE_TAMPON - 1);
        if (nb_lus <= 0)
            break;
        tampon[nb_lus] = '\0';  /* ajout d'un terminateur de chaîne */
        printf("%s", tampon);
    }
    /* et fin */
    close(fd);
    printf("CLIENT> Fin.\n");
    return EXIT_SUCCESS;
}
