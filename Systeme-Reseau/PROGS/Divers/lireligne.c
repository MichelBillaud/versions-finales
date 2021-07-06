/* lireligne.c */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define CONTENANCE_INITIALE 16

char *lire_nouvelle_ligne(void);

int main(void)
{
    printf("tapez une grande ligne\n");
    char *nouvelle_ligne = lire_nouvelle_ligne();
    if (nouvelle_ligne == NULL) {
        fprintf(stderr, "Plus de place en mémoire\n");
        return EXIT_FAILURE;
    }
    printf("%s\n", nouvelle_ligne);
    free(nouvelle_ligne);
    return EXIT_SUCCESS;
}

char *lire_nouvelle_ligne(void)
{
    /*
       Renvoie un tampon de texte contenant une ligne
       lue sur l'entrée standard.
       Un nouveau tampon est créé à chaque invocation.
       Renvoie NULL en cas de problème d'allocation
    */

    int taille   = 0;
    int contenance = CONTENANCE_INITIALE;
    char *chaine = malloc(contenance);

    if (chaine == NULL) {          // ne devrait pas se produire
        return NULL;                 // mais il vaut mieux vérifier
    }

    while (true) {
        int c = getchar();
        if ((c == '\n') || (c == EOF)) {
            break;
        }
        chaine[taille++] = c;
        if (taille == contenance) {    // au besoin agrandir pour caser
            contenance *= 2;             // au moins le caractère nul de fin
            char *chaine_plus_grande = realloc(chaine, contenance);
            if (chaine_plus_grande == NULL) {
                free(chaine);
                return NULL;
            }
            chaine = chaine_plus_grande;
        }
    };
    chaine[taille] = '\0';
    return chaine;
}

