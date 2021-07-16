/**
 * Allocations et libérations. A compléter
 * Un tableau de personnes
 */
#include <stdio.h>
#include <stdlib.h>

struct Employe {
  char prenom[20];
  int  bureau;
};

struct Employe *nouveauTableau(int nb)
{
  struct Employe *t
    = malloc(nb * sizeof(struct Employe));
  if (t == NULL) {
    fprintf(stderr, "échec d'allocation");
    exit (EXIT_FAILURE);
  }
  return t;
}

int main()
{
  int nbEmployes;
  printf("Combien d'employés ? ");
  scanf("%d", & nbEmployes);

  struct Employe *tableau = nouveauTableau(nbEmployes);
  
  for (int i = 0; i < nb; i++) {
    lire_employe( & tableau[i]);
  }
  for (int i = 0; i < nb; i++) {
    afficher_employe( & tableau[i]);
  }

  free(tableau);                      // libération
  exit (EXIT_SUCCESS);
}
