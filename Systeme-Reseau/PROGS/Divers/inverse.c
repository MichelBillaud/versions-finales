/*
  Divers/inverse.c

  Affichage des lignes d'un fichier en partant de la fin
  Exemple d'utilisation de mmap

  M. Billaud, Octobre 2002, corrigé Juin 2018 :-)
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

void abandon (char message[], char nom_fichier[]);
void afficher_a_l_envers (const char *texte, size_t taille);
int  trouver_fd_et_taille(int *adr_fd,
                          size_t *adr_taille,
                          const char nom_fichier[]);

int main(int argc, char * argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s fichier\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *nom_fichier = argv[1];

    int fd;
    size_t taille;
    trouver_fd_et_taille(& fd, & taille, nom_fichier);

    char *texte = mmap(NULL, taille, PROT_READ, MAP_PRIVATE, fd, 0);
    if (texte == MAP_FAILED) {
        abandon("Mise en mémoire", nom_fichier);
    }
    afficher_a_l_envers(texte, taille);

    if (munmap(texte, taille) < 0) {
        abandon("Détachement", nom_fichier);
    }

    close(fd);
    return EXIT_SUCCESS;
}

void abandon (char message[], char nom_fichier[])
{
    char tampon[200];
    snprintf(tampon, 200, "\"%s\" : %s", nom_fichier, message);
    perror(tampon);
    exit(EXIT_FAILURE);
}

/* affichage à l'envers du contenu d'un tampon de texte */

void afficher_a_l_envers (const char *adr_debut_texte, size_t taille)
{
    const char *adr_fin_ligne = adr_debut_texte + taille - 1;

    for (const char *p = adr_fin_ligne - 1; p >= adr_debut_texte; p--) {
        if (*p == '\n') {  // position fin de ligne précédente
            int longueur = adr_fin_ligne - p;    // longueur ligne
            write(STDOUT_FILENO, p + 1,  longueur);
            adr_fin_ligne = p;
        };
    }
    // affichage première ligne
    int longueur = adr_fin_ligne - adr_debut_texte + 1;
    write(STDOUT_FILENO, adr_debut_texte, longueur);
}

int trouver_fd_et_taille(int *adr_fd, size_t *adr_taille,
                         const char nom_fichier[])
{
    struct stat etat;
    if (stat(nom_fichier, &etat) != 0) {
        return 1;
    }

    if (! S_ISREG(etat.st_mode)) {
        return 2;
    }

    *adr_fd = open(nom_fichier, O_RDONLY);
    if (*adr_fd < 0) {
        return 3;
    }
    *adr_taille = etat.st_size;
    return 0;
}

