## Les données en mémoire

Un programme C contient généralement des variables. Pendant l'exécution,
chaque variable est stockée en mémoire quand elle n'est pas 
éliminée par le compilateur (ce qui arrive quand il détecte que la
variable est inutile, ou suffisamment temporaire pour être rangée dans
un registre du processeur), dans un **emplacement en mémoire** formé
d'octets consécutifs.

### Taille des données, opérateur `sizeof()`

Le nombre d'octets (la **taille**) dépend du type de la variable. On la
détermine en appliquant l'opérateur `sizeof()` à une variable ou à un
type.

Le listing ci-dessous montre un programme qui fait afficher les tailles
de quelques types. 

~~~C
/**
 * Affichage des tailles de divers types de base.
 * 
 * Les tailles dépendent du compilateur, 
 * sauf pour pour char (toujours 1).
 */
#include <stdio.h>

int main()
{
    printf("char\t%zu\n",   sizeof(char)); 
    printf("int\t%zu\n",    sizeof(int));
    printf("long\t%zu\n",   sizeof(long));
    printf("float\t%zu\n",  sizeof(float));
    printf("double\t%zu\n", sizeof(double));
    return 0;
}
~~~

Le résultat  dépend des choix d'implémentation du
compilateur que vous utilisez, sauf pour le type le type `char` qui
correspond **toujours** [^15] à un octet exactement. [^11]

Exécution du programme :

    type	taille
    ----	------
    char	1
    int	    4
    long	8
    float	4
    double	8

Par exemple, un `int` occupe *en général* 4 octets sur une machine 32
bits, et 8 octets sur une machine 64 bits.

**Remarques :**

1.  `sizeof()` retourne un `size_t`, type qui correspond à un entier non
    signé assez grand pour stocker une taille. L'implémentation de
    `size_t` (`unsigned int`, `unsigned long`, \...) est dépendante de
    l'architecture.

2.  Portabilité : utilisez la spécification de format `%zu` pour le type
    `size_t`.

### Structures en mémoire

Rappel : une structure contient un ou plusieurs membres (champs) qui
peuvent être de types différents. Exemple de définition d'un type et
d'une variable :

~~~C
struct Employe {
  char nom[40];
  int  age;
};

struct Employe cuistot  = { "Maurice", 63 };
~~~

**Exercice :** 
Écrivez un programme montrant un exemple de structure dont la taille
n'est pas *égale* à la somme des tailles des champs.

### Adresse des données, opérateur "`&`"

Le programme ci-dessous fait afficher les adresses de quelques variables
pendant l'exécution, obtenues en leur appliquant l'opérateur "`&`"
(`address-of`)[^12] du langage C.

~~~C
/**
 * Affichage d'adresses de variables.
 * 
 */
#include <stdio.h>

int glob1 = 12;
float glob2 = 34;

int main()
{
    int loc1 = 33;
    float loc2 = 3.14;
    printf("var.\tadresse\n----\t------\n");
    printf("glob1\t%p\n",  (void *)  & glob1); 
    printf("glob2\t%p\n",  (void *)  & glob2);
    printf("loc1\t%p\n",   (void *)  & loc1);
    printf("loc2\t%p\n",   (void *)  & loc2);
    return 0;
}
~~~

Résultat de l'exécution

    var.	adresse
    ----	------
    glob1	0x5594b04a9038
    glob2	0x5594b04a903c
    loc1	0x7fffa1c515fc
    loc2	0x7fffa1c515f8

Les adresses sont des données typées : par exemple l'adresse d'une
variable de type `int` est de type `int*`. L'affichage se fait avec la
spécification "`%p`\" (pour *pointer*) en les convertissant en "adresses
non-typées" (`void *`).

**Remarques :**

-   Les variables globales du programme et les variables locales de la
    fonction `main()` sont dans des "segments" dont les adresses
    diffèrent considérablement : le segment de données pour les
    variables globales, et le segment de pile pour les autres[^13].

-   Sur les systèmes d'exploitation modernes, les adresses virtuelles
    qui s'affichent changent à chaque exécution[^14].

**Exercice :**
Reprenez l'exemple de structure
dont la taille est supérieure à la
somme des tailles des champs, et définissez une variable de ce type.
Faites afficher l'adresse et la taille de la structure et de chacun de
ses champs. Conclusion ?

### Tableaux et adresses

Le programme ci-dessous fait affiche l'adresse d'un tableau et de ses
éléments.

~~~C
/**
 * Affichage d'adresses tableaux / éléments
 */
#include <stdio.h>

int main()
{
  int tab[4] = { 11, 22, 33, 44 };
  
  printf("var.\tadresse\n----\t------\n");
  printf("tab\t%p\n",  (void *) tab);
  for (int i = 0; i < 4; i++) {  
    printf("tab[%d]\t%p\n",  i, (void *)  & tab[i]);
  }
  return 0;
}
~~~

Résultat :

    var.	adresse
    ----	------
    tab	0x7ffd7b053230
    tab[0]	0x7ffd7b053230
    tab[1]	0x7ffd7b053234
    tab[2]	0x7ffd7b053238
    tab[3]	0x7ffd7b05323c

**Remarque :**
En C, une variable de type tableau désigne en fait l'*adresse* de
l'emplacement qui a été réservé en mémoire pour placer les
éléments. Il n'y a dons pas besoin de mettre un "`&`" devant `tab`
dans le `printf`.

On constate qu'à l'exécution, les éléments se suivent en mémoire, et
l'adresse du tableau correspond à celle du premier élément.

[^11]: Il a été nommé `char` à une époque où le codage d'un caractère
    tenait toujours sur un octet (codages ANSI, EBCDIC, \...). Si
    c'était à refaire, ce type s'appellerait certainement `byte`.

[^12]: Il s'agit ici des *adresses virtuelles*, dans l'espace mémoire où
    le système a chargé le processus.

[^13]: Sur une machine qui supporte la notion de segmentation,
    évidemment. Ce n'est pas le cas des petits micro-contrôleurs dans le
    domaine de l'informatique embarquée

[^14]: C'est une mesure de sécurité pour éviter l'exploitation de
    "débordements de tampon" et autres erreurs de programmation. Lors du
    chargement d'un programme, le système d'exploitation choisit des
    adresses aléatoires pour placer les segments dans l'espace mémoire
    virtuel du processus.

[^15]: Presque toujours. Il y a des complications sur les machines
    dont les mots sont de 36 bits, etc.
