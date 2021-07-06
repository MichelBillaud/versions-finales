/* TCP-Flots/client-web.c */

/*
   Interrogation d'un serveur web

   Usage:
   client-web serveur port adresse-document

   retourne le contenu du document d'adresse
   http://serveur:port/adresse-document

   Exemple:
   client-web www.info.prive 80 /index.html

   Fonctionnement:
   - ouverture d'une connexion TCP vers serveur:port
   - envoi de la requête   GET adresse-document HTTP/1.0[cr][lf][cr][lf]
   - affichage de la réponse
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
#include <stdbool.h>

#define CRLF "\r\n"
#define TAILLE_TAMPON 1000

void abandon(char message[])
{
    perror(message);
    exit(EXIT_FAILURE);
}

/* -- connexion vers un serveur TCP --------------------------- */

int ouvrir_connexion_tcp(const char hote[], const char service[])
{
    // construction adresse du serveur à contacter

    struct addrinfo indications = {
        .ai_family = AF_UNSPEC,
        .ai_socktype = SOCK_STREAM
    };
    struct addrinfo *premier;
    int r = getaddrinfo(hote, service, & indications, & premier);

    if (r != 0 ) {
        abandon("Adresse serveur incorrecte");
    }

    if (premier == NULL) {
        abandon("Adresse serveur inconnue");
    }
    // création prise, et connexion à l'adresse

    int fd = socket(premier->ai_family, SOCK_STREAM, 0);
    if (fd < 0) {
        abandon("échec création socket");
    }
    if (connect(fd, (struct sockaddr *) premier->ai_addr,
            premier->ai_addrlen) < 0) {
        abandon("Echec connexion");
    }

    freeaddrinfo(premier);
    
    return (fd);
}

/* ------------------------------------------------------ */

void demander_document(int fd, char adresse_document[])
{
    char requete[TAILLE_TAMPON];
    /* constitution de la requête, suivie d'une ligne vide */
    int longueur = snprintf(requete, TAILLE_TAMPON,
            "GET %s HTTP/1.0" CRLF CRLF,
            adresse_document);
    write(fd, requete, longueur); /* envoi */
}

/* ------------------------------------------------------ */

void afficher_reponse(int fd)
{
    while (true) {
        /* lecture par bloc */
        char tampon[TAILLE_TAMPON];
        int longueur = read(fd, tampon, TAILLE_TAMPON);
        if (longueur <= 0) {
            break;
        }
        write(1, tampon, longueur); /* copie sur sortie standard */
    };
}

/* -- main --------------------------------------------------- */

int main(int argc, char *argv[])
{  
    /* pour tests : 
    char *hote = "127.0.0.1";
    char *service = "80";
    char *adresse_document = "/";
    */  
    
    if (argc != 4) {
        printf("Usage: %s hote service adresse-document\n",
                argv[0]);
        abandon("nombre de paramètres incorrect");
    }

    char *hote = argv[1];
    char *service = argv[2];
    char *adresse_document = argv[3];
  
    int fd = ouvrir_connexion_tcp(hote, service);
    demander_document(fd, adresse_document);
    afficher_reponse(fd);
    close(fd);

    return EXIT_SUCCESS;
}
