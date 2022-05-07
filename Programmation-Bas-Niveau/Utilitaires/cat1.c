// cat1.c
// affiche le contenu d'un fichier sur la sortie standard
//
// usage: cat1 fichier


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s fichier\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* ouverture */
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror ("ouverture");
        return EXIT_FAILURE;
    }
    
    /* est-ce un fichier normal , pas un répertoire etc ? */
    struct stat s;
    fstat(fd, &s);
    if ( ! S_ISREG(s.st_mode)) {
        fprintf(stderr, "%s n'est pas un fichier\n", argv[1]);
        return EXIT_FAILURE;
    }
    
    /* copie sur la sortie standard, bloc par bloc */
    char buffer[1024];
    ssize_t nb;
    while( (nb = read(fd, buffer, 1024)) > 0) {
        write(fd, buffer, nb);
    }

    /* fermeture */
    close(fd);
    
    return EXIT_SUCCESS;
}

