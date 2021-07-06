/* Divers/taille.c */
/*
	indique la taille et la nature
	des "fichiers" cités en paramètres
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

const char *nom_mode(mode_t mode);

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s fichier ... \n", argv[0]);
        exit(EXIT_FAILURE);
    };

    for (int k=1 ; k<argc ; k++) {
        printf("%20s:\t", argv[k]);
        struct stat status;
        if (stat(argv[k], &status) == 0) {
            printf("taille %8ld, type %s",
                   status.st_size,
                   nom_mode(status.st_mode));
        } else {
            switch(errno) {
            case ENOENT :
                printf("le fichier n'existe pas");
                break;
            default:
                printf("erreur %s", strerror(errno));
                break;
            }
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
}

const char *nom_mode(mode_t mode)
{
    return S_ISREG(mode)    ? "fichier"
           :    S_ISLNK(mode)  ? "lien symbolique"
           :    S_ISDIR(mode)  ? "répertoire"
           :    S_ISCHR(mode)  ? "périphérique mode caractère"
           :    S_ISBLK(mode)  ? "péripherique mode bloc"
           :    S_ISFIFO(mode) ? "fifo"
           :    S_ISSOCK(mode) ? "socket"
           :    "inconnu";
}
