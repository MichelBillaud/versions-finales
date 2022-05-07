#include <search.h>
#include <stdio.h>
#include <stdbool.h>

#include "table-des-symboles.h"

void visiterSymbole(const void *p, VISIT x, const int level /* unused */)
{
  struct Symbole *s = *(struct Symbole **) p;
  if (x == postorder || x == leaf) {
    printf("nom=%s, \tligne=%d, \tvaleur=%d :", 
	   s->nom, s->ligne, s->valeur);
    for (int i=0; i < s->nbRef; i++) {
      printf("%d ", s->tRef[i].ligne);
    }
    printf("\n");
  }
}

void afficherTable()
{
  printf("afficherTable\n");
  twalk(tableDesSymboles, visiterSymbole); 
}

int main(void)
{
  initialiserTableDesSymboles();
  definirSymbole("a", 1, 1);
  ajouterReference("b", 2, 0, 0);
  definirSymbole("c", 3, 3);
  ajouterReference("b", 4, 0, 0);
  definirSymbole("b", 5, 5);
  ajouterReference("d", 6, 0, 0);
  afficherTable();
}

