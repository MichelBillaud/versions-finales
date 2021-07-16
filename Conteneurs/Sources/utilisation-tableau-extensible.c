#include <stdio.h>
#include <stdlib.h>

#include "tab_int.h"

void afficher(const char *m, const struct tab_int *a);

int main()
{
  struct tab_int tableau;
  ti_init(& tableau);

   // 10, 20 ... 100
  for (int v = 10; v <= 100; v += 10) { 
    ti_ajouter(& tableau, v);
  }

  afficher("avant", & tableau);
  ti_changer(& tableau, 3, 421);
  afficher("après", & tableau);

  ti_detruire(& tableau);
  
  exit (0);
}

/**
 * affiche un message et le contenu d'un tableau
 * @param m : chaine
 * @param a : adresse du tableau
 */
void afficher(const char *m,
	      const struct tab_int *a)
{
  printf("%s: ", m);
  int taille = ti_taille(a);
  for (int i = 0;  i < taille; i++) {
    printf("%d ", ti_valeur(a, i));
  }
  printf("\n");
}
     
