


#include <stdio.h>

void affiche_hexa(char nom[], void *adresse, int longueur) {
  
  printf("%10s en hexa : ", nom);
  char * tableau = adresse;
  for (int i = 0; i < longueur; i++) {
     printf("%02x", tableau[i]);
  }
  printf("\n");
}

int main()
{
  int entier = 33;
  float flottant = 3.14;
  affiche_hexa("un int"  , & entier,   sizeof entier);
  affiche_hexa("un float", & flottant, sizeof flottant);
  printf("\n");
	
	return 0;
}

