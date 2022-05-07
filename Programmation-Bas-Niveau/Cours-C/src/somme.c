#include <stdio.h>
#include <stdlib.h>

int somme(const int x, const int y)
{
  return x+y;
}

int main()
{
  int a, b;
  printf ("Donnez deux nombres : ");
  scanf("%d %d", &a, &b);
  printf("la somme %d + %d vaut %d\n", a, b, somme(a,b));
  return EXIT_SUCCESS;
}
