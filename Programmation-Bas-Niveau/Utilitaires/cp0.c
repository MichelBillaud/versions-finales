// cp0.c
// copie d'un fichier
//  usage : cp0 src dest

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <fcntl.h>


#define PATH_MAX 2048

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "usage: %s src dst\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* ouvertures */
    int in = open(argv[1], O_RDONLY);
    if (in < 0) {
        perror ("ouverture fichier entree");
        return EXIT_FAILURE;
    }
    int out = open(argv[2], O_WRONLY | O_CREAT, 0644);
    if (out < 0) {
        perror ("ouverture fichier sortie");
        return EXIT_FAILURE;
    }
    
    /* copie bloc par bloc */
    char buffer[1024];
    ssize_t nb;
    while( (nb = read(in, buffer, 1024)) > 0) {
        write(out, buffer, nb);
    }

    /* fermeture */
    close(in);
    close(out);
    return EXIT_SUCCESS;
}

