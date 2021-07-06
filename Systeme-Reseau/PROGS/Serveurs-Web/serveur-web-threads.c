/* serveur-web.c */

/* ------------------------------------------------
   Serveur TCP

   serveur web, qui renvoie les fichiers (textes)
   d'un répertoire sous forme de pages HTML

  usage :  serveur-web [-p port] [-d repertoire]
  exemple: serveur-web -p 8000 -d /usr/doc/exemples

  Version basée sur les threads. Au lieu de créer
  un processus par connexion, on gère un pool de tâches
  (sous-serveurs).
  - au démarrage du serveur les sous-serveurs sont créés,
  et bloqués par un verrou
  - quand un client se connecte, la connexion est
  confiée à un sous-serveur inactif, qui est débloqué
  pour l'occasion.
--------------------------------------------------*/

#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <netdb.h>
#include <bits/local_lim.h>

#include "constantes.h"
#include "reseau.h"
#include "traitement-client.h"

#define NB_SOUS_SERVEURS 5

struct DonneesThread {
    pthread_t id; //  identificateur de thread
    pthread_mutex_t verrou;
    bool actif; //  sous-serveur occupé
    int fd; // socket du client
    char *racine_documents;
};

// variables globales
struct DonneesThread threads[NB_SOUS_SERVEURS];
bool serveur_en_marche;

/* -------------------------------------------------------------
 Traitement des signaux
--------------------------------------------------------------- */

void arreter_serveur(/* int numero_signal */)
{
    serveur_en_marche = false;
}

/* -------------------------------------------------------
   sous_serveur
   ------------------------------------------------------- */
void *executer_sous_serveur(void *ptr)
{
    struct DonneesThread *adr_donnees = ptr;
    while (true) {
        pthread_mutex_lock(&adr_donnees->verrou);
        servir_client(adr_donnees->fd,
                adr_donnees->racine_documents);
        close(adr_donnees->fd);
        adr_donnees->actif = false;
    }
    return NULL; /* jamais exécuté */
}

/* ------------------------------------------------------- */
void creer_sous_serveurs(char repertoire[])
{
    for (int k = 0; k < NB_SOUS_SERVEURS; k++) {
        struct DonneesThread *adr_donnees = &(threads[k]);
        adr_donnees->actif = false;
        adr_donnees->racine_documents = repertoire;
        pthread_mutex_init(&adr_donnees->verrou, NULL);
        pthread_mutex_lock(&adr_donnees->verrou);
        pthread_create(&adr_donnees->id, NULL,
                executer_sous_serveur, adr_donnees);
    }
}

void supprimer_sous_serveurs()
{
    for (int k = 0; k < NB_SOUS_SERVEURS; k++) {
        pthread_kill(threads[k].id, SIGKILL);
    }
}

void affecter_sous_serveur(int numero_client, int fd_client)
{
    struct sockaddr_storage a;
    socklen_t l = sizeof a;
    getsockname(fd_client, (struct sockaddr *) &a, &l);
    char ip[HOST_NAME_MAX], port[20];
    getnameinfo((struct sockaddr *) & a, l, 
        ip, sizeof(ip), 
        port, sizeof(port),
            NI_NUMERICHOST | NI_NUMERICSERV);
    
    /* recherche d'un sous-serveur inoccupé */
    for (int k = 0; k < NB_SOUS_SERVEURS; k++) {
        if (!threads[k].actif) {
            // affectation du travail et déblocage
            printf("> client %d [%s port %s] traité par sous-serveur %d\n",
                    numero_client, ip, port, k);
            threads[k].fd = fd_client;
            threads[k].actif = true;
            pthread_mutex_unlock(&threads[k].verrou);
            return;
        }
    }
    // tout le monde est occupé...
    printf("> client %d [%s port %s] rejeté (surcharge)\n",
            numero_client, ip, port);
    close(fd_client);
}

/* -----------------------------------------------------
   demarrer_serveur: crée le socket serveur
   et lance des processus pour chaque client
   ----------------------------------------------------- */

void demarrer_serveur(const char port[], char racine_documents[])
{
    printf("> Serveur " VERSION "+threads "
            "(port=%s, répertoire de documents=\"%s\")\n",
            port, racine_documents);

    /* signal SIGINT -> arrêt du serveur */
    struct sigaction action_fin = {
        .sa_flags = 0
    };
    sigemptyset(&action_fin.sa_mask);
    sigaction(SIGINT, &action_fin, NULL);

    /* création du socket serveur et du pool de sous-serveurs */
    serveur_en_marche = true;
    int fd_serveur = ouvrir_serveur_tcp(port);
    creer_sous_serveurs(racine_documents);

    /* boucle du serveur */
    int numero_client = 0;
    while (serveur_en_marche) {
        int fd_client = ouvrir_client(fd_serveur);
        numero_client++;
        affecter_sous_serveur(numero_client, fd_client);
    }
    printf("=> fin du serveur\n");
    supprimer_sous_serveurs();
    shutdown(fd_serveur, SHUT_RDWR); /* utile ? */
    close(fd_serveur);
}

/* -------------------------------------------------------------*/
void usage(char prog[])
{
    printf("Usage : %s [options\n\n", prog);
    printf("Options :"
            "-h\tcemessage\n"
            "-p port\tport du serveur          [%s]\n"
            "-d dir \trépertoire des documents [%s]\n",
            PORT_PAR_DEFAUT, REPERTOIRE_PAR_DEFAUT);
}

/* -------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    char *port = PORT_PAR_DEFAUT;
    char *racine_documents
            = REPERTOIRE_PAR_DEFAUT; /*  racine des documents */
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
                racine_documents = optarg;
                break;
            case '?':
                fprintf(stderr,
                        "Option inconnue -%c. -h pour aide.\n", optopt);
                break;
        }
    demarrer_serveur(port, racine_documents);
    exit(EXIT_SUCCESS);
}
