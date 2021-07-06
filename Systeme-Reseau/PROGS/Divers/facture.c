/* facture.c */

/* exemple printf(), scanf() */

#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    char  article[10];
    float prix;
    int   quantite;

    printf("article, prix unitaire, quantité ?\n");
    int nb_variables_lues = scanf("%s %f %d",
                                  article,
                                  & prix,
                                  & quantite);

    if (nb_variables_lues != 3) {
        printf("Erreur dans les données");
        return EXIT_FAILURE;
    }

    printf("%d %s à %10.2f =  %10.2f\n",
           quantite,
           article,
           prix,
           prix * quantite);

    return EXIT_SUCCESS;
}
