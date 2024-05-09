/* Divers/redirection.c */

/*
  Le fichier cité en paramètre est passé à travers
  la commande wc.
*/

#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>

const char COMMANDE [] = "wc";

int main (int argc, char * argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s fichier\n", argv[0]);
        return EXIT_FAILURE;
    }

    int fd_fichier = open(argv[1], O_RDONLY);
    assert (fd_fichier >= 0);

    /* transfert du descripteur dans celui de l'entrée standard */
    assert (dup2(fd_fichier, STDIN_FILENO) >= 0);

    close(fd_fichier);

    system(COMMANDE); // l'entrée standard est reliée au fichier

    assert(errno == 0);
    return EXIT_SUCCESS;
}

