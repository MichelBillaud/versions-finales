/*
  resolution.c

  Résolution d'adresses
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <limits.h>

void resoudre_nom(const char nom_machine[]);

int main(int argc, char *argv[])
{
    if (argc == 1) {
        printf("usage: %s adresses...\n", argv[0]);
        return EXIT_FAILURE;
    }
    for (int i = 1; i < argc; i++) {
        resoudre_nom(argv[i]);
    }
    return EXIT_SUCCESS;
}

void resoudre_nom(const char nom_machine[])
{
    printf("* Résolution de %s\n", nom_machine);
    struct addrinfo *adr_liste_adresses;

    // le type de socket est précisé pour n'avoir qu'une réponse par numéro IP
    struct addrinfo indications = {
        .ai_family = AF_UNSPEC,
        .ai_socktype = SOCK_STREAM
    };

    int r = getaddrinfo(nom_machine, NULL,
            &indications,
            & adr_liste_adresses);
    if (r != 0) {
        printf("- échec de la résolution\n");
        return;
    };
    for (struct addrinfo *ptr = adr_liste_adresses;
            ptr != NULL;
            ptr = ptr->ai_next) {
        // conversion  adresse -> hote
        char ip_hote[HOST_NAME_MAX]; // taille max FQDN, RFC 1035
        getnameinfo(ptr->ai_addr, ptr->ai_addrlen,
                ip_hote, sizeof(ip_hote),
                NULL, 0, // port non utilisé
                NI_NUMERICHOST);
        printf("-> %s\n", ip_hote);
    }
    printf("\n");
    freeaddrinfo(adr_liste_adresses);
}
