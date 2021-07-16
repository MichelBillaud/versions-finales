/**
 * Affichage d'adresses tableaux / éléments
 */
#include <stdio.h>

int main()
{
  int tab[4] = { 11, 22, 33, 44 };
  
  printf("var.\tadresse\n----\t------\n");
  printf("tab\t%p\n",  (void *) tab);
  for (int i = 0; i < 4; i++) {  
    printf("tab[%d]\t%p\n",  i, (void *)  & tab[i]);
  }
  return 0;
}

