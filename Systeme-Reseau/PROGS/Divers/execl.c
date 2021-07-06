/* Divers/execl.c */

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
    char nom_fichier[TAILLE_MAX_NOMFICHIER];

    printf("Préfixe du fichier à compiler : ");
    scanf("%s", prefixe);                     /* dangereux */

    snprintf(nom_fichier, TAILLE_MAX_NOMFICHIER,
             "%s.c", prefixe);

    execl(CHEMIN_COMPILATEUR,
          NOM_COMPILATEUR,
          nom_fichier, "-o", prefixe,
          NULL);

    perror("execl");            /* on ne passe jamais ici */
    return EXIT_FAILURE;
}
