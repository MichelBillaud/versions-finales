/* Divers/droits.c */

/*
 * met les droits 0600 sur un ou plusieurs fichiers
 * (illustration de chmod() et errno)
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define DROITS  (S_IRUSR | S_IWUSR)

void ecrire_message_erreur (int numero_erreur);

int main(int argc, char *argv[])
{
    for (int k = 1; k < argc; k++) {
        printf("%s: ", argv[k]);
        if (chmod(argv[k], DROITS) == 0) {
            printf("fichier protégé");
        } else {
            ecrire_message_erreur(errno);
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
}

void ecrire_message_erreur (int numero_erreur)
{
    switch (numero_erreur) {
    case EACCES :
        printf("impossible de consulter un des répertoires du chemin");
        break;
    case ELOOP :
        printf("trop de liens symboliques (boucles ?)");
        break;
    case ENAMETOOLONG :
        printf("le nom est trop long");
        break;
    case ENOENT :
        printf("le fichier n'existe pas");
        break;
    case EPERM :
        printf("permission refusée");
        break;
    default:
        printf("erreur %s", strerror(numero_erreur));
        break;
    }
}
