/*
  Echo-Datagrammes/serveur-echo.c -  Réception de datagrammes

  Exemple de serveur qui
  - ouvre un socket (IPV6) sur un port en mode non-connecté
  - affiche les messages (chaînes de caractères) qu'il reçoit par ce socket,
 ainsi que leur provenance. 
  - envoie une réponse : la chaine en majuscules
 */


#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <netdb.h>

#define FAMILLE   AF_INET6

#define TAILLE_TAMPON 1000
static int fd;

void abandon(char message[])
{
    printf("SERVEUR> Erreur fatale\n");
    perror(message);
    exit(EXIT_FAILURE);
}

void arreter_serveur(int signal)
{
    close(fd);
    printf("SERVEUR> Arrêt du serveur (signal %d)\n", signal);
    exit(EXIT_SUCCESS);
}

int socket_serveur_datagrammes(const char *service)
{
    struct addrinfo indications = {
        .ai_family = FAMILLE, 
        .ai_flags = AI_PASSIVE
    };

    struct addrinfo *adr_liste_adresses;
    int r = getaddrinfo(NULL, service, & indications, & adr_liste_adresses);
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
        r = bind(fd, ptr->ai_addr, ptr->ai_addrlen);
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

int fabriquer_reponse(const char requete[], char reponse[])
{
    int taille = 0;
    while (requete[taille] != '\0') {
        reponse[taille] = toupper(requete[taille]);
        taille++;
    };
    return taille;
}

int main(int argc, char *argv[])
{
    /* 1. réception des paramètres de la ligne de commande */

    if (argc != 2) {
        printf("usage: %s port\n", argv[0]);
        abandon("mauvais nombre de paramètres");
    }
    char * nom_service = argv[1];

    /* 2. Si une interruption se produit, arrêt du serveur */
    /* signal(SIGINT, arreter_serveur); */

    struct sigaction a = {
        .sa_handler = arreter_serveur,
        .sa_flags = 0,
    };
    sigemptyset(&a.sa_mask);

    sigaction(SIGINT, &a, NULL);

    /* 3. Initialisation du socket de réception */

    int fd = socket_serveur_datagrammes(nom_service);
    if (fd < 0) {
        abandon("socket");
    }

    printf("SERVEUR> Le serveur écoute le port %s\n",
            nom_service);

    while (true) {
        struct sockaddr_storage adresse_client;
        char tampon_requete[TAILLE_TAMPON],
                tampon_reponse[TAILLE_TAMPON];

        /* 4. Attente d'un datagramme (requête) */

        socklen_t taille_adresse_client = sizeof (adresse_client);
        ssize_t lg_requete = recvfrom(fd, tampon_requete, TAILLE_TAMPON,
                0, /* flags */
                (struct sockaddr *) &adresse_client,
                & taille_adresse_client);
        if (lg_requete < 0) {
            abandon("recvfrom");
        }

        /* 5. Affichage message avec sa provenance et sa longueur */
        char hote_client[INET6_ADDRSTRLEN];
        char port_client[8];
        getnameinfo((struct sockaddr *) & adresse_client, taille_adresse_client,
                hote_client, sizeof (hote_client),
                port_client, sizeof (port_client),
                NI_NUMERICHOST | NI_NUMERICSERV
                );

        printf("%s:%s [%ld]\t: %s\n",
                hote_client, port_client, lg_requete, tampon_requete);

        /* 6. Fabrication d'une réponse */

        int taille_reponse = fabriquer_reponse(tampon_requete, tampon_reponse);

        /* 7. Envoi de la réponse */

        if (sendto(fd,
                tampon_reponse,
                taille_reponse,
                0,
                (struct sockaddr *) &adresse_client,
                sizeof adresse_client) < 0) {
            abandon("Envoi de la réponse");
        }
    }
    /* on ne passe jamais ici */
    return EXIT_SUCCESS;
}
