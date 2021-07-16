

#include <stdio.h>
#include <stdbool.h>


bool est_positif(int *p) {
  return *p >= 0;
}

typedef bool (*Predicat)(void *);

int compter(void * tableau, int taille_tableau, int taille_element, Predicat critere) {
    int nombre = 0;

    void * ptr = tableau;
    for (int i=0; i<taille_tableau; i++) {
      if (critere(ptr)) {
        nombre ++;
      }
      ptr = (char *)(ptr) + taille_element;
    }
    return nombre;
}

int main()
{
  int tableau[] = {-1, -2, 3, -4, 5 };
  int n = compter(tableau, 5, sizeof (int), (Predicat) est_positif);
  printf("%d\n", n);
	return 0;
}

