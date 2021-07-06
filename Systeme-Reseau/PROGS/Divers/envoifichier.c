/*
 * Divers/envoifichier.c
 *
 * Illustration de system();
 */

#include <stdio.h>
#include <stdlib.h>

const int TAILLE_MAX_COMMANDE   = 100;
const int TAILLE_MAX_ADRESSE    = 100;
const int TAILLE_MAX_NOMFICHIER = 100;

int main(void)
{
    char destinataire[TAILLE_MAX_ADRESSE];
    char nom_fichier[TAILLE_MAX_NOMFICHIER];
    char commande[TAILLE_MAX_COMMANDE];
    int reponse;

    printf("e-mail destinataire ?\n");
    scanf("%s",destinataire);                  /* dangereux */
    printf("nom du fichier à envoyer ?\n");
    scanf("%s",nom_fichier);            /* dangereux */

    snprintf(commande,TAILLE_MAX_COMMANDE,
             "uuencode %s %s | mail %s",
             nom_fichier, nom_fichier, destinataire);

    reponse = system(commande);
    if (reponse == EXIT_SUCCESS) {
        printf("OK\n");
    } else {
        printf("La commande retourne : %d\n",reponse);
    }
    return EXIT_SUCCESS;
}

