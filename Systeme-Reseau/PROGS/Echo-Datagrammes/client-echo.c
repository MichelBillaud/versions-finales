/*
  Echo-Datagrammes/client-echo.c

  Envoi de datagrammes

  Exemple de client qui
  - ouvre un socket
  - envoie un datagramme sur ce socket (ligne de texte)
  - attend une réponse
  - affiche la réponse

  Usage :
      ./client-echo  hote  port  "chaine de texte"

  L'hote peut être un nom de machine, ou une adresse numérique IPv4/IPv6
  Le port un nom de service ou un numéro
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define TAILLE_TAMPON 1000

int fd_serveur;

void abandon(char message[])
{
    printf("CLIENT> Erreur fatale\n");
    perror(message);
    exit(EXIT_FAILURE);
}

int socket_vers_serveur_datagrammes(const char *serveur, const char *service)
{
    struct addrinfo *adr_liste_adresses;
    int r = getaddrinfo(serveur, service, NULL, & adr_liste_adresses);
    if (r != 0) {
        printf("Erreur %s\n", gai_strerror(r));
        abandon("Echec de résolution d'adresses");
    };
    int fd = -1;

    for (struct addrinfo *ptr = adr_liste_adresses;
            ptr != NULL;
            ptr = ptr->ai_next) {

        fd = socket(ptr->ai_family, SOCK_DGRAM, 0);
        if (fd < 0) {
            continue;
        }
        r = connect(fd, ptr->ai_addr, ptr->ai_addrlen);
        if (r < 0) {
            close(fd);
            fd = -1;
        } else {
            break; // on a trouvé un socket qui marche.
        }
    }
    freeaddrinfo(adr_liste_adresses);
    return fd;
}

int main(int argc, char *argv[])
{
    /* 1. réception des paramètres de la ligne de commande */
    if (argc != 4) {
        printf("Usage: %s hote port message\n", argv[0]);
        abandon("nombre de paramètres incorrect");
    }
    char * nom_serveur = argv[1];
    char * nom_service = argv[2];
    char * requete = argv[3];

    /* 2. Initialisation du socket */

    fd_serveur = socket_vers_serveur_datagrammes(nom_serveur, nom_service);

    /* 3. Envoi de la requête */
    printf("envoi> %s\n", requete);
    int longueur_requete = strlen(requete) + 1;
    if (send(fd_serveur, requete, longueur_requete, 0) < 0) {
        abandon("Envoi requete");
    };

    /* 4. Lecture de la réponse */
    char reponse[TAILLE_TAMPON];
    int longueur_reponse = recv(fd_serveur, reponse, TAILLE_TAMPON, 0);
    if (longueur_reponse < 0) {
        abandon("Attente réponse");
    }
    printf("réponse> %s\n", reponse);
    close(fd_serveur);

    printf("fin>\n");
    return EXIT_SUCCESS;
}
