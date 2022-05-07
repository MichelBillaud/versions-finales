/*
  table des symboles

  A chaque symbole (chaîne) sont associés

  - le numéro de la ligne où il est défini (-1: indéfini, 0: prédéfini) 
  - sa valeur (si défini)
  - la liste des endroits où il est employé (references)
        - numéro de ligne
	- la rustine (patch) à appliquer au code généré
             - position dans le code
	     - masque 

   Par exemple position=42 et masque=0x0FF signifie que la valeur du symbole
   devra être mise dans l'octet de poids faible du mot de position 42.
*/

#include <search.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "table-des-symboles.h"


void * tableDesSymboles;

void initialiserTableDesSymboles()
{
  tableDesSymboles = NULL;
}


int comparerSymbole(const void *a, const void *  b)
{
  struct Symbole 
    * pa = (struct Symbole *) a,
    * pb = (struct Symbole *) b;
  return strcmp(pa->nom, pb->nom);
}

struct Symbole *  creerSymbole(char nom[]) 
{
  char *strdup(const char s[]);
  struct Symbole *s = malloc(sizeof(struct Symbole));
  s -> nom = strdup(nom);
  s -> ligne = -1;
  s -> valeur = 0;
  s -> nbRef = s -> maxRef = 0;
  s -> tRef  = NULL;
  // printf("tsearch %s\n",nom);
  tsearch(s,&tableDesSymboles, comparerSymbole); 
  return s;
}

struct Symbole * chercherSymbole(char nom[])
{
  struct Symbole 
    requete = { nom, 0, 0,  0, 0, NULL };
  void *r = tfind ( & requete, &tableDesSymboles, comparerSymbole);
  return (r ==NULL) ? creerSymbole(nom) : *(struct Symbole **) r;
}

/* 
   retourne 1 si ok
*/
bool symboleEstDefini(char * nom) {
  struct Symbole *s = chercherSymbole(nom);
  return s->ligne >= 0;
}

void definirSymbole(char nom[], int ligne, int valeur)
{
  struct Symbole *s = chercherSymbole(nom);
  s -> ligne = ligne;
  s -> valeur = valeur;
}

void ajouterReference(char nom[], int ligne, int position, int masque)
{
  struct Symbole *s = chercherSymbole(nom);

  // au besoin ajouter de la place pour des références supplémentaires
  if (s->nbRef == s->maxRef) {
    s->maxRef = (s->maxRef == 0) ? 8 : 2*s->maxRef;
    s->tRef = realloc(s->tRef, s->maxRef * sizeof(struct Reference));
  }
  struct Reference * r = s->tRef + (s->nbRef++);
  r -> ligne    = ligne;
  r -> position = position;
  r -> masque   = masque;
}
