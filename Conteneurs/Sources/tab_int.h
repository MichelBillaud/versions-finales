#ifndef TAB_INT_H
#define TAB_INT_H

struct tab_int {
  int  taille;
  int  capacite;
  int *elements;
};

void ti_init    (      struct tab_int *a);          
void ti_ajouter (      struct tab_int *a, int valeur);
void ti_detruire(      struct tab_int *a);
int  ti_taille  (const struct tab_int *a); 
int  ti_valeur  (const struct tab_int *a, int indice);
void ti_changer (      struct tab_int *a, int indice,
		                          int valeur);
#endif
