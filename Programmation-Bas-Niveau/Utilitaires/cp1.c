// cp1.c
// copie d'un fichier
//  usage : cp1 src dest

// src doit être un fichier
// dst peut être un répertoire

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>


#define PATH_MAX 2048

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "usage: %s src dst\n", argv[0]);
        return EXIT_FAILURE;
    }
    char src_path[PATH_MAX], 
         dst_path[PATH_MAX];
    
    strcpy(src_path, argv[1]);
    strcpy(dst_path, argv[2]);
     
    /* verification src */
    struct stat s;
    if ((stat(src_path, &s) != 0)
       || ! S_ISREG(s.st_mode)) {
        fprintf(stderr, "%s n'est pas un fichier\n", argv[1]);
        return EXIT_FAILURE;
    }
    
    /* verification dst */
    if (stat(dst_path, &s) == 0) {
      if ( S_ISDIR(s.st_mode)) {
        /* répertoire : construction du nom de fichier */
        strcat(dst_path, "/");
        char * pos = rindex(src_path, '/');
        pos = (pos == NULL) ? src_path : pos + 1;
        strcat(dst_path, pos);
      } 
    }
       
    /* ouvertures */
    int in = open(src_path, O_RDONLY);
    if (in < 0) {
        perror ("ouverture fichier entree");
        return EXIT_FAILURE;
    }
    int out = open(dst_path, O_WRONLY | O_CREAT, 0644);
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

