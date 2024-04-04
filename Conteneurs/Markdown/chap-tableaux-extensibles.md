## Tableaux extensibles


Nous appellons *tableau extensible* une structure de données qui sert à
stocker des éléments, et qui

-   comme un tableau ordinaire, permet de désigner un élément par sa
    position (première = 0, seconde = 1, etc.), pour le modifier ou le
    consulter.

-   à la différence des tableaux, permet d'ajouter des éléments à la fin
    sans limite de taille[^21].

Ici nous allons prendre l'exemple des tableaux extensibles d'entiers.

### Choix d'une API, exemple d'utilisation

-   Le type "tableau extensible d'entiers" se matérialise par une
    structure appelée `tab_int`.

-   Une famille de fonctions, dont le nom est préfixé par "`ti`"
    représentera les actions qui agissent dessus.

-   Le premier paramètre de ces fonctions sera toujours l'adresse du
    tableau concerné.[^22]

Le programme suivant montre l'emploi d'un tel tableau :

~~~C
#include <stdio.h>
#include <stdlib.h>

#include "tab_int.h"

void afficher(const char *m, const struct tab_int *a);

int main()
{
  struct tab_int tableau;
  ti_init(& tableau);

   // 10, 20 ... 100
  for (int v = 10; v <= 100; v += 10) { 
    ti_ajouter(& tableau, v);
  }

  afficher("avant", & tableau);
  ti_changer(& tableau, 3, 421);
  afficher("après", & tableau);

  ti_detruire(& tableau);
  
  exit (0);
}

/**
 * affiche un message et le contenu d'un tableau
 * @param m : chaine
 * @param a : adresse du tableau
 */
void afficher(const char *m,
	      const struct tab_int *a)
{
  printf("%s: ", m);
  int taille = ti_taille(a);
  for (int i = 0;  i < taille; i++) {
    printf("%d ", ti_valeur(a, i));
  }
  printf("\n");
}
~~~

Il remplit un tableau avec des valeurs de 10 en 10, et modifie l'une
d'elles. Affichage des résultats avant et après modification :

~~~
    avant: 10 20 30 40 50 60 70 80 90 100 
    après: 10 20 30 421 50 60 70 80 90 100 
~~~


### L'implémentation


#### Données

Un tableau extensible est représenté par

-   un **tableau** alloué dynamiquement, pouvant accueillir un certain
    nombre d'éléments (sa **capacité**),

-   un entier indiquant le nombre d'éléments utilisés, au début du
    tableau (sa **taille**)

~~~C
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
void ti_changer (      struct tab_int *a, int indice, int valeur);
#endif
~~~

#### Code

Le code comporte quelques choix d'implémentation :

-   la capacité initiale, lorsqu'on initialise un tableau extensible
    (ici, 4 éléments)

-   la stratégie d'agrandissement en cas de débordement. Ici on double :
    l'ajout du 5ième élément ré-alloue le tableau avec une capacité de 8,
    et l'ajout du 8ième porte la capacité à 16. Cette stratégie est
    justifiée plus loin.

~~~C
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
  a-> taille += 1;
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
~~~

### Stratégie de doublement de la capacité {#strategiedoublement}

Lorsque le tableau est plein, on le ré-alloue avec une capacité
supérieure.

La stratégie de doublement de cette capacité est, contrairement à ce
que suggère l'intuition (souvent trompeuse pour ce genre de choses),
**très efficace** en terme de nombre de copies : au cours du remplissage,
chaque élément a été copié **au plus une fois** en moyenne.

Raisonnement pour s'en convaincre :

1. Imaginons qu'à un moment le *vector* ait grandi jusqu'à 500 éléments.
Comme le tableau grandit en doublant de taille, sa capacité est la
première puissance de 2 supérieure à 500, soit 512.
2. Le tableau sera agrandi (et ré-alloué) en ajoutant le 513ieme, sa
capacité passera à 1024 éléments, et pour cela il faudra ré-allouer ce
qui provoquera la copie des 512 éléments existants. Coût : 512, si on
prend comme unité de compte la copie d'un élément.
3. Mais pour arriver à 513, il avait fallu copier 256 éléments. Et pour
arriver à 257, en copier 128.
4. Si on fait le total, si on en est au 513-ième élément ajouté (et
jusqu'au 1024-ième) on a fait en tout $256 + 128 + 64 + ...$ copies
d'éléments, ce qui est plus petit que 512.

Conclusion : Dans le pire des cas (ajout du 513 ième), le coût moyen
d'ajout d'un élément est inférieur à $512/513$ : il y a donc eu
**moins d'une copie par élément**.

**Exercice :** 
En général la première idée qui vient est d'augmenter d'une unité la
capacité à chaque ajout. Évaluez le coût de cette stratégie.

[^21]: autre que les limitations de l'allocation dynamique

[^22]: pour les deux raisons évoquées plus haut :
    -   c'est obligatoire pour les fonctions qui modifient le tableau
    -   c'est souhaitable pour les autres, pour éviter de faire des
        copies. Dans ce cas on mettra un `const`.
