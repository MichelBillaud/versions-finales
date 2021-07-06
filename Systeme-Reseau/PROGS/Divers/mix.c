/* Divers/mix.c */

/*
   affiche les données qui proviennent de 2 fifos
   usage:  mix f1 f2
*/

#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>

#define TAILLE_TAMPON 128

/*
   Mixe les données en provenance de deux
   descripteurs
*/

void mixer(int fd1, int fd2, int sortie)
{
    fd_set fds_ouverts;  /* les descripteurs ouverts */

    FD_ZERO (&fds_ouverts);
    FD_SET  (fd1, &fds_ouverts);
    FD_SET  (fd2, &fds_ouverts);
    int nb_fds_ouverts = 2;

    /* tant qu'il reste des descripteurs ouverts.... */

    while (nb_fds_ouverts > 0) {
        char tampon[TAILLE_TAMPON];

        /* on attend qu'un descripteur au moins soit prêt ...*/
        fd_set fds_prets = fds_ouverts;
        assert (select(FD_SETSIZE, &fds_prets, NULL, NULL, NULL) >= 0 );

        if (FD_ISSET(fd1, &fds_prets)) {   // fd1 est-il prêt ?

            int nb_octets_lus = read(fd1, tampon, TAILLE_TAMPON);
            if(nb_octets_lus >= 0) {
                write(sortie, tampon, nb_octets_lus);
            } else {
                close(fd1);         // fin de fd1 : on l'enlève
                nb_fds_ouverts--;
                FD_CLR(fd1, &fds_ouverts);
            }
        }

        if (FD_ISSET(fd2, &fds_prets)) {
            int nb_octets_lus = read(fd2, tampon, TAILLE_TAMPON);
            if(nb_octets_lus >= 0) {
                write(sortie, tampon, nb_octets_lus);
            } else {
                close(fd2);
                nb_fds_ouverts--;
                FD_CLR(fd2, &fds_ouverts);
            }
        }
    }
}

int main (int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage : %s f1 f2\n", argv[0]);
        return EXIT_FAILURE;
    }

    int fd1 = open(argv[1], O_RDONLY);
    assert(fd1 >= 0);

    int fd2 = open(argv[2], O_RDONLY);
    assert(fd2 >= 0);

    mixer(fd1, fd2, 1);

    return EXIT_SUCCESS;
}
