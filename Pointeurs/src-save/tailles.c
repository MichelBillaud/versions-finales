#include <stdio.h>

#define P(nom,T) printf("taille de " nom "\t = %ld bits\n", 8*sizeof(T))

int main()
{
  P("entier",int);
  P("entier long", long);
  P("flottant", float);
  P("double", double);
  P("pointeur", void *);

  return 0;
}

