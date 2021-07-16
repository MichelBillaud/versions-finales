## Pointeurs

On appelle **pointeur**[^1] une donnée qui contient une adresse,
c'est-à-dire la position d'une (autre) donnée en mémoire.


On emploie les pointeurs pour diverses raisons, en particulier :

- le passage de paramètres,
- le parcours de tableaux,
- la manipulation des données allouées dynamiquement.


### Déclaration des pointeurs

Pour **déclarer** un pointeur destiné à contenir des adresses d'objets de
type T, on précède son nom par une étoile. Exemples :

~~~C
int *pi;               // pointeur sur un int
struct Personne *pp;   // pointeur sur struct Personne
~~~


Pour déclarer un tableau de pointeurs, le nom du tableau est précédé par
une étoile :

~~~C
char *noms[10];  // tableau de 10 pointeurs de caractères
~~~

La règle générale est qu'en C, la déclaration d'une variable ressemble à
son usage (voir l'indirection ci-dessous).

### Pointeurs non-typés, conversions


Les pointeurs non-typés sont déclarés avec `void *`.

~~~C
int entier = 123;
void *adresse = & entier;        // pointeur non typé
printf("valeur=%d, adresse=%p\n",
               entier,      adresse);
~~~

**Remarque :**
l'expression "`& entier`" de la seconde ligne est de type `int *`, mais
il y a une **conversion implicite** entre les adresses typées et
non-typées.

### Indirection, opérateur "`*`"

L'opérateur "`*`" fournit un accès à la donnée dont l'adresse est
contenue dans un pointeur **typé**. Exemple :

~~~C
int nombre = 12;
int *p = & nombre;            // pointeur typé (entiers)

*p = 33;                      // modif. à travers p
printf("= %d\n", *p);         // accès indirect
~~~


**Terminologie :**
on dit que

-   la variable `nombre` **est pointée par** `p`.
-   on fait une **indirection** pour, à partir d'un pointeur, accéder à
    la donnée qu'il pointe.
-   on **dé-référence** le pointeur.

***Remarque :**
dans l'exemple d'un tableau de pointeurs de caractères vu plus haut,

-   `noms[2]` est le troisième[^2] pointeur ;

-   `*noms[2]` est le `char` désigné par ce pointeur.

Et puisque `*noms[i]` est un `char`, dans la logique de C, il n'est pas
anormal que la déclaration d'un tableau de pointeurs

~~~C
  char   *noms[10];
~~~

ressemble fortement à l'usage qu'on a des éléments.

### Le pointeur `NULL`

La constante `NULL` est une valeur conventionnelle (de type `void*` que
l'on affecte à un pointeur pour indiquer qu'il **ne contient pas**, à un
moment donné, l'adresse d'un objet en mémoire. Le pointeur ne pointe sur
rien.[^3]

Quand un pointeur contient `NULL`, tenter de le dé-référencer est un
**comportement indéfini**, qui provoque généralement un arrêt brutal de
l'exécution :

~~~C
  int *p = NULL;
  *p = 12;            // crash
~~~

### Pointeurs de structures, notation "`->`"


Selon les règles de priorités d'opérateurs de C, "`*a.b`" se lit
"`*(a.b)`".

La notation `pointeur->champ` facilite la désignation d'un champ d'une
structure dont on a l'adresse dans un pointeur. Exemple :

~~~C
struct Point {
  float x, y;
};
...
struct Point *p;  // p pointeur de point

p->x = 0.0;          // au lieu de  (*p).x = 0.0
p->y = 0.0;
~~~

## Passage de paramètres

Le langage C ne connaissant que le passage de paramètres **par valeur**,
on utilise des pointeurs pour simuler le "passage de référence" dans
deux situations :

1.  l'action que l'on veut coder modifie un objet qu'on lui indique,

2.  les objets que l'on souhaite transmettre sont assez gros, et pour
    des raisons de performance, on veut éviter la copie inhérente à un
    passage par valeur.

### Pointeur pour le passage par référence

Exemple : une action consistant à échanger les nombres contenus dans
deux variables. On la traduit par une fonction à qui on passe les
**adresses** des variables à modifier.

~~~C
void echanger(int *pa, int *pb) {
  int tmp = *pa;
  *pa = *pb;
  *pb = tmp;
}

// usage
int a = 34, b = 23;
echanger( & a, & b);
~~~

### Pointeur pour éviter de copier

Exemple: affichage d'une structure.

~~~C
      struct Personne {
        char nom[100];
        char prenom[100];
        ...
      };
      
      void afficher_personne(const struct Personne *p) {
        printf("nom = %s\n'', p->nom);
        ...
      }
~~~

Le mot-clé `const` annonce nos intentions. La déclaration de paramètre
se lit de droite à gauche : `p` est un pointeur vers une structure
`Personne` qu'on ne modifie pas.

### Parcours de tableau, arithmétique des pointeurs

Une chaîne de caractères est un tableau d'octets terminé par un
caractère nul.

~~~C
  char test[] = "abc";  // tableau de _4_ octets
~~~

Pour parcourir une chaîne, on peut[^4] utiliser un pointeur qui va
désigner tour à tour chaque octet :

~~~C
  void affiche_codes(const char chaine[]) {
    char *p = chaine;
    while (*p != '\0') {
      printf("-> %d\n"; *p);
      p++;
    }
  }
~~~

**Remarques**

1.  Un tableau déclaré en paramètre est en réalité un pointeur.

2.  l'incrémentation d'un pointeur (`p++]`) modifie ce pointeur pour
    qu'il désigne l'élément suivant[^5]

[^1]: Ce terme est aussi (hélas) souvent employé par extension pour
    désigner les adresses elles-mêmes. Nous essaierons d'éviter ce
    regrettable manque de rigueur, source de confusions, qui permettrait
    d'écrire qu'un pointeur (au sens de variable) *contient* un pointeur
    (au sens d'adresse)...



[^2]: le premier a l'indice 0\...

[^3]: Ne pas confondre avec un pointeur non-initialisé, qui contient une
    valeur aléatoire

[^4]: à la place d'un indice

[^5]: la valeur numérique du pointeur - celle qu'on voit avec `printf` -
    est augmentée de la taille du type pointé (ici 1, parce que c'est un
    `char`.
