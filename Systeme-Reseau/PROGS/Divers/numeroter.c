/*
 * Divers/numeroter.c
 *
 * Illustration de getline();
 * affiche le contenu de fichiers de texte, en numérotant les lignes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char **argv)
{
    // le même tampon sert pour toutes les lectures
    char *tampon = NULL;
    size_t taille_tampon = 0;

    int numero = 0;

    for (int i = 1; i < argc; i++) {
        FILE *fichier = fopen(argv[i], "r");
        if (fichier == NULL) {
            fprintf(stderr, "Fichier %s absent ou protégé\n", argv[i]);
            continue;
        }
        while (true) {
            // Lecture. Le tampon est alloué/agrandi au besoin
            ssize_t taille_ligne = getline(& tampon, & taille_tampon, fichier);
            if (taille_ligne < 0) {
                break;
            }
            // caractère de fin de ligne déjà présent dans le tampon
            printf("%03d\t%s", ++numero, tampon);
        }
        fclose(fichier);
    }

	// libération du tampon
    free(tampon);

    return EXIT_SUCCESS;
}

