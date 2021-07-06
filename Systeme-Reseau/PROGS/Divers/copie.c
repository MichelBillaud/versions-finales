/* copie.c */

/*
   Entrées-sorties de bas niveau
   Usages:
   1: copie              (entrée-standard -> sortie standard)
   2: copie fichier      (fichier -> sortie standard)
   3: copie source dest  (source -> dest)
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

#define TAILLE_TAMPON   4096

void transfert(int fd_entree, int fd_sortie);

int main(int argc, char *argv[])
{
    int fd_entree, fd_sortie;

    switch(argc) {
    case 1 :
        transfert(STDIN_FILENO, STDOUT_FILENO);
        break;
    case 2:
        fd_entree = open(argv[1], O_RDONLY);
        transfert(fd_entree, STDOUT_FILENO);
        close(fd_entree);
        break;
    case 3:
        fd_entree = open(argv[1], O_RDONLY);
        fd_sortie = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0666);
        transfert(fd_entree, fd_sortie);
        close(fd_entree);
        close(fd_sortie);
        break;
    default:
        printf("Usage: copie [src [dest]]\n");
        break;
    }
    return EXIT_SUCCESS ;
}

void transfert(int fd_entree, int fd_sortie)
{
    char tampon[TAILLE_TAMPON];

    assert( fd_entree >= 0);
    assert( fd_sortie >= 0);

    for(;;) {
        int nb_octets_lus = read(fd_entree, tampon, TAILLE_TAMPON);
        if (nb_octets_lus <= 0) {
            break;
        }
        int nb_octets_ecrits = write(fd_sortie, tampon, nb_octets_lus);
        assert(nb_octets_ecrits == nb_octets_lus);
    }
}
