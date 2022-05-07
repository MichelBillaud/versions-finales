#include <stdio.h>
#include <stdlib.h>

int main()
{
  char nom[100];
  int  annee;

  printf ("Quel est votre nom ? ");
  scanf("%s", nom);
  printf ("Et votre annee de naissance ? ");
  scanf("%d", &annee);
  printf ("Bonjour %s, vous avez %d ans !\n", nom, 2013-annee);

  return EXIT_SUCCESS;
}
