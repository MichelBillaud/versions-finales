/*
  SelectFifo/lecteur.c

  Exemple de lecture avec délai (timeout).
  M. Billaud, Septembre 2002 - revu 2016

  Ce programme attend des lignes de texte provenant d'une fifo,
  et les affiche.
  En attendant de recevoir les lignes, il affiche une petite étoile
  tournante (par affichage successif des symboles  - \ | et /).

  Exemple d'utilisation:
  - créer une fifo :  mkfifo /tmp/mafifo
  - dans une fenêtre, lancer : lecteur /tmp/mafifo
  le programme se met en attente
  - dans une autre fenêtre, faire
  cat > /tmp/mafifo
  puis taper quelques lignes de texte.

 */

#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>

#define TAILLE_TAMPON 100
#define DELAI         500  /* millisecondes */

#define SYMBOLES      "-\\|/"
#define NBSYMBOLES    4

void montrer_animation();

int attendre_donnees(int fd, int millisecondes);

void afficher_donnees(int fd);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, " Usage: %s fifo\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    printf("> Ouverture fifo %s ...\n", argv[1]);
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Ouverture refusée\n");
        exit(EXIT_FAILURE);
    };
    printf("OK\n");

    afficher_donnees(fd);

    close(fd);
    exit(EXIT_SUCCESS);
}

// -------------------------------------------------------

void afficher_donnees(int fd)
{
    int numero_ligne = 1;
    while (true) {
        int r = attendre_donnees(fd, DELAI);
        if (r == 0) { // rien reçu
            montrer_animation();
        } else { // on a reçu quelque chose
            char tampon[TAILLE_TAMPON];
            int nb_octets_lus = read(fd, tampon, TAILLE_TAMPON - 1);
            if (nb_octets_lus <= 0) { // fin
                break;
            }
            tampon[nb_octets_lus] = '\0';
            printf("%4d %s", numero_ligne, tampon);
			numero_ligne += 1;
        }
    }
}

int attendre_donnees(int fd, int millisecondes)
{
    fd_set set;
    FD_ZERO(&set);
    FD_SET(fd, &set);

    struct timeval delai = {
        .tv_sec   = millisecondes / 1000,
        .tv_usec = (millisecondes % 1000) * 1000
    };

    return select(FD_SETSIZE, &set, NULL, NULL, & delai);
}

void montrer_animation()
{
    static int n = 0;
    printf("%c\b", SYMBOLES[n++ % NBSYMBOLES]);
    fflush(stdout);
}
