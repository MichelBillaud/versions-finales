#include <stdio.h>
#include <stdlib.h>

void saisirDeuxNombres(int *px, int *py)
{
  printf("Donnez deux nombres : ");
  scanf("%d %d", px, py);
}

void calculerSomme(const int x, const int y, int *pz)
{
  *pz = x+y;
}

void afficherSomme(const int x, const int y, const int z)
{
  printf("la somme %d + %d vaut %d\n", x, y, z);
}

int main()
{
  int a, b, c;
  saisirDeuxNombres( &a, &b    );
  calculerSomme    (  a,  b, &c);
  afficherSomme    (  a,  b,  c);
  return EXIT_SUCCESS;
}
