/*
  paire-send.c

  échange de données à travers des sockets locaux créés par
  socketpair()
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdbool.h>

struct paquet {
    int type;
    int valeur;
};

/* les différents types de paquets */

#define DONNEE   0
#define RESULTAT 1
#define FIN      2

void abandon(char message[])
{
    perror(message);
    exit(EXIT_FAILURE);
}

int additionneur(int fd)
{
    /*
       calcule la somme des entiers qui arrivent sur le descripteur,
       renvoie le résultat
    */
    int somme = 0;
    while(true) {
        struct paquet recu;
        int n = recv(fd, &recu, sizeof recu, 0);
        if (n < 0)
            abandon("recv");
        printf("additionneur: réception d'un paquet contenant ");
        if (recu.type == FIN) {
            printf("la marque de fin\n");
            break;
        }
        printf("la donnée %d\n", recu.valeur);
        somme += recu.valeur;
    };
    /* envoi reponse */

    struct paquet reponse;
    reponse.type = RESULTAT;
    reponse.valeur = somme;
    printf("additionneur: envoi du total %d\n", somme);
    int n = send(fd, &reponse, sizeof reponse, 0);
    if (n < 0) {
        abandon("additionneur: send");
    }
    return EXIT_SUCCESS;
}

int generateur(int fd)
{
    /*
       envoie une suite d'entiers, récupère et affiche le résultat.
     */

    struct paquet p;

    for (int i = 1; i <= 5; i++) {
        p.type = DONNEE;
        p.valeur = i;
        printf("génerateur: envoi de la donnée %d\n", i);
        int n = send(fd, &p, sizeof p, 0);
        if (n < 0)
            abandon("generateur: send");
        sleep(1);
    };
    p.type = FIN;
    printf("génerateur: envoi de la marque de fin\n");
    int n = send(fd, &p, sizeof p, 0);
    if (n < 0) {
        abandon("generateur: send");
    }
    printf("generateur: lecture du résultat\n");
    n = recv(fd, &p, sizeof p, 0);
    if (n < 0) {
        abandon("generateur: recv");
    }
    int resultat = p.valeur;
    printf("generateur: resultat reçu = %d\n", resultat);
    return EXIT_SUCCESS;
}

int main()
{
    int paire_sockets[2];

    socketpair(AF_LOCAL, SOCK_DGRAM, 0, paire_sockets);

    if (fork() == 0) {
        close(paire_sockets[0]);
        return additionneur(paire_sockets[1]);
    } else {
        close(paire_sockets[1]);
        return generateur(paire_sockets[0]);
    }
}
