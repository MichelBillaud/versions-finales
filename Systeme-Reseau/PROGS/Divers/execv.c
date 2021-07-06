/* Divers/execv.c */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define CHEMIN_COMPILATEUR    "/usr/bin/gcc"
#define NOM_COMPILATEUR       "gcc"
#define TAILLE_MAX_PREFIXE    10
#define TAILLE_MAX_NOMFICHIER 100


int main(void)
{
    char prefixe[TAILLE_MAX_PREFIXE];
    char nom_source[TAILLE_MAX_NOMFICHIER];

    char *parametres[] = {
        NOM_COMPILATEUR,
        NULL, /* emplacement pour le nom du fichier source */
        "-o",
        NULL, /* emplacement pour le nom de l'exécutable   */
        NULL  /* fin des paramètres       */
    };

    printf("préfixe du fichier à compiler : ");
    scanf("%s", prefixe);        /* dangereux */

    snprintf(nom_source, TAILLE_MAX_NOMFICHIER,
             "%s.c", prefixe);

    parametres[1] = nom_source;
    parametres[3] = prefixe;

    execv(CHEMIN_COMPILATEUR, parametres);

    perror("execv"); /* normalement on ne passe pas ici */
    return EXIT_FAILURE;
}
