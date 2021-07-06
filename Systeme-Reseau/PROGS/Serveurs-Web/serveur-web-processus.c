/* Serveur-avec-processus/serveur-web.c */

/* ------------------------------------------------
   Serveur TCP

   serveur web, qui renvoie les fichiers (textes)
   d'un répertoire sous forme de pages HTML

  usage :  serveur-web [-p port] [-d repertoire]
  exemple: serveur-web -p 8000 -d /usr/doc/exemples
--------------------------------------------------*/

#include <unistd.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <netdb.h>
#include <limits.h>

#include "constantes.h"
#include "reseau.h"

#include "traitement-client.h"

/* variable globale, pour partager
          avec traitement signal fin_serveur */

bool serveur_en_marche;

static void arreter_serveur(/* int numero_signal */)
{
    serveur_en_marche = false;
}

static void attendre_sous_serveur(/* int numero_signal */)
{
    /* cette fonction est appelée chaque fois
       qu'un signal SIGCHLD
       indique la fin d'un processus fils _au moins_.  */
    while (waitpid(-1, NULL, WNOHANG) > 0) {
        /* attente des fils arrêtés, tant qu'il y en a */
        continue;
    }
}

static void installer_signaux()
{
    struct sigaction action_int, action_chld;
    /* arrêt du serveur si signal SIGINT */
    action_int.sa_handler = arreter_serveur;
    sigemptyset(&action_int.sa_mask);
    action_int.sa_flags = 0;
    sigaction(SIGINT, &action_int, NULL);

    /* attente fils si SIGCHLD */
    action_chld.sa_handler = attendre_sous_serveur;
    sigemptyset(&action_chld.sa_mask);
    action_chld.sa_flags = SA_NOCLDSTOP;
    sigaction(SIGCHLD, &action_chld, NULL);
}

static void afficher_informations_client(int fd_client, int numero_client)
{
    struct sockaddr_storage adresse_client;
    socklen_t long_adresse_client = sizeof adresse_client;

    char hote[HOST_NAME_MAX];
    char service[20]; 

    getpeername(fd_client,
            (struct sockaddr *) &adresse_client, &long_adresse_client);
    getnameinfo((struct sockaddr *)& adresse_client,  
            long_adresse_client,
            hote, sizeof(hote),
            service, sizeof(service),
            NI_NUMERICHOST | NI_NUMERICSERV);
            
    printf("> client %d : %s [%s]\n", numero_client, hote, service);
}

static void demarrer_serveur(const char port[], char repertoire[])
{
    installer_signaux();

    serveur_en_marche = true;
    int fd_serveur = ouvrir_serveur_tcp(port);

    printf("> Serveur " VERSION
           " (port=%s, répertoire de documents=\"%s\")\n",
           port, repertoire);

    for (int numero_client = 1; serveur_en_marche; numero_client++) {
        int fd_client = ouvrir_client(fd_serveur);
        afficher_informations_client(fd_client, numero_client);
        if (fork() == 0) {
            close(fd_serveur);
            servir_client(fd_client, repertoire);
            close(fd_client);
            exit(EXIT_SUCCESS);
        }
        close(fd_client);
    }
    shutdown(fd_serveur, SHUT_RDWR);
    printf("> Arrêt du serveur\n");
}

/* -------------------------------------------------------------*/

static void usage(char prog[])
{
    printf("Usage : %s [options\n\n", prog);
    printf("Options :"
           "-h\tcemessage\n"
           "-p port\tport du serveur          [%s]\n"
           "-d dir \trépertoire des documents [%s]\n",
           PORT_PAR_DEFAUT, REPERTOIRE_PAR_DEFAUT);
}

/* -------------------------------------------------------------*/
int main(int argc, char * argv[])
{
    char *port = PORT_PAR_DEFAUT;
    char *repertoire = REPERTOIRE_PAR_DEFAUT; /* la racine
					       des documents */
    char c;
    while ((c = getopt(argc, argv, "hp:d:")) != -1)
        switch (c) {
        case 'h':
            usage(argv[0]);
            exit(EXIT_SUCCESS);
            break;
        case 'p':
            port = optarg;
            break;
        case 'd':
            repertoire = optarg;
            break;
        case '?':
            fprintf(stderr, "Option inconnue -%c. "
                    "-h pour aide.\n",
                    optopt);
            break;
        };
    demarrer_serveur(port, repertoire);
    exit(EXIT_SUCCESS);
}
