## Allocation dynamique

L'**allocation dynamique de mémoire** est un ensemble de fonctionnalités
mises à la disposition du programmeur d'application par la bibliothèque
standard C.

Elle lui permet de gérer de l'espace mémoire supplémentaire (en plus de
la pile d'exécution et du segment de données) pour y placer des données,
en spécifiant le nombre d'octets voulu. Elle permet aussi de libérer un
espace alloué dont on n'a plus besoin.

### Attention, danger

L'usage de l'allocation dynamique impose un soin très attentif au
programmeur qui est guetté par deux dangers :

-   **la fuite mémoire** si un programme alloue en boucle des zones
    mémoires, sans les libérer quand il n'en n'a plus besoin. L'espace
    mémoire du programme s'agrandit indéfiniment, ce qui finit mal.

-   la **corruption des données** si un programme utilise par erreur une
    zone qui a été libérée.

C'est une difficulté typique de la programmation en C.

### Fonctions `malloc()` et `free()`


Nous utilisons essentiellement deux fonctions, définies dans `stdlib.h` :

-   `malloc()` pour obtenir de l'espace mémoire supplémentaire,
-   `free()` pour restituer (libérer) de l'espace obtenu par `malloc()`,

et occasionnellement `realloc()` qui agrandit ou rétrécit un espace
qu'on a obtenu, quitte à le déménager ailleurs.

Le listing ci-dessous montre l'utilisation d'un tableau de structures
alloué dynamiquement.

~~~C
/**
 * Allocations et libérations. A compléter
 * Un tableau de personnes
 */
#include <stdio.h>
#include <stdlib.h>

struct Employe {
  char prenom[20];
  int  bureau;
};

struct Employe *nouveauTableau(int nb)
{
  struct Employe *t
    = malloc(nb * sizeof(struct Employe));
  if (t == NULL) {
    fprintf(stderr, "échec d'allocation");
    exit (EXIT_FAILURE);
  }
  return t;
}

int main()
{
  int nbEmployes;
  printf("Combien d'employés ? ");
  scanf("%d", & nbEmployes);

  struct Employe *tableau = nouveauTableau(nbEmployes);
  
  for (int i = 0; i < nb; i++) {
    lire_employe( & tableau[i]);
  }
  for (int i = 0; i < nb; i++) {
    afficher_employe( & tableau[i]);
  }

  free(tableau);                      // libération
  exit (EXIT_SUCCESS);
}
~~~

Pour l'allocation par `malloc()`, on indique en paramètre la taille
(nombre d'octets) souhaitée. La fonction retourne l'adresse (non typée)
de la zone allouée, ou `NULL` en cas d'échec..

Pour libérer une zone, on fournit son adresse à la fonction `free`.

### Exercice :

Écrire les fonctions manquantes.

### Réallocation (`realloc`)

Si on veut ajouter un employé supplémentaire, il faut agrandir le
tableau. Pour cela on fait un appel à `realloc()` en indiquant

-   l'adresse de la zone que l'on veut redimensionner (ici `tableau`),
-   la nouvelle taille

et `realloc` retournera l'adresse de la nouvelle zone :

~~~C
nbElements += 1;
tableau = realloc(tableau,
                  nbElements * sizeof(struct Employe));
~~~

**À savoir :**

-   si le premier paramètre de `realloc` est `NULL`, la fonction se
    comporte comme `malloc()`,

-   vous l'aviez deviné : en cas d'échec, `realloc()` retourne `NULL`.

**Exercice**

Écrivez un programme qui

-   part d'un tableau vide,
-   fait une boucle, en demandant si on veut en ajouter d'autres,
-   les affiche tous à la fin.
 
