/* Divers/comptage.c */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void traiter_fichier(const char *nom_fichier)
{
    FILE *f = fopen(nom_fichier, "r");
    if (f == NULL) {
        fprintf(stderr, "%-20s: absent ou illisible\n", nom_fichier);
        return;
    };
    int nb_caracteres = 0;
    int nb_lignes     = 0;
    int c;
    while ( (c = fgetc(f)) != EOF) {
        nb_caracteres += 1;
        if (c == '\n') {
            nb_lignes += 1;
        }
    }
    printf("%-20s: %d cars, %d lignes\n",
           nom_fichier,
           nb_caracteres,
           nb_lignes);
    fclose(f);
}

int main (int argc, char *argv[])
{
    const char *nom_programme = argv[0];

    if (argc == 1) {
        fprintf(stderr, "Usage: %s fichier...\n", nom_programme);
        return EXIT_FAILURE;
    }
    for (int i = 1; i < argc; i++) {
        traiter_fichier(argv[i]);
    }

    return EXIT_SUCCESS;
}
