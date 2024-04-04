#include <stdlib.h>
#include "tab_int.h"

#define CAPACITE_MINIMALE 4

void ti_init (struct tab_int *a)
{
  a->taille = 0;
  a->capacite = CAPACITE_MINIMALE;
  // NOTE : on devrait vérifier le résultat de malloc
  a->elements = malloc(a->capacite * sizeof(int));
}

void ti_ajouter(struct tab_int *a, int valeur)
{
  // si plein, agrandir
  if (a->taille == a->capacite) {
    a->capacite *= 2;
    // NOTE : on devrait vérifier le résultat de realloc    
    a->elements = realloc(a->elements,
			  a->capacite * sizeof(int));
  }
  // ajout à la fin
  a->elements[a->taille] = valeur;
  a->taille += 1;
}

void ti_detruire(struct tab_int *a)
{
  a->taille = 0;
  a->capacite = 0;
  free(a->elements);
  a -> elements = NULL;
}

int ti_taille(const struct tab_int *a) 
{
  return a->taille;
}

// les indices doivent être entre 0  et a->taille - 1

int ti_valeur(const struct tab_int *a, int indice)
{
  return a->elements[indice];
}

void ti_changer(struct tab_int *a, int indice,
		int valeur)
{
  a->elements[indice] = valeur;
}

