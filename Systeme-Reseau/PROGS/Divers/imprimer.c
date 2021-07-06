/*
 * Divers/imprimer.c
 *
 * Illustration de system();
 */

#include <stdio.h>
#include <stdlib.h>

#define TAILLE_MAX_COMMANDE    150
#define TAILLE_MAX_NOM_FICHIER  100

#define FORMAT_COMMANDE_IMPRESSION  "a2ps -4 -A page %s"

int main(void)
{
    char nom_fichier[TAILLE_MAX_NOM_FICHIER];
    printf("nom du fichier ? ");
    fgets(nom_fichier, TAILLE_MAX_NOM_FICHIER, stdin);

    char commande[TAILLE_MAX_COMMANDE];
    snprintf(commande, TAILLE_MAX_COMMANDE,
             FORMAT_COMMANDE_IMPRESSION,
             nom_fichier);

    int resultat = system(commande);

    if (resultat == EXIT_SUCCESS) {
        printf("OK\n");
    } else {
        printf("La commande retourne : %d\n", resultat);
    }
    return resultat;
}

