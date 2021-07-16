## Ensemble de chaînes, hachage

Dans cette partie, nous montrons comment représenter **efficacement** un
ensemble[^31] de chaînes de caractères en utilisant une **fonction de
hachage**.

### Opérations de base


Les opérations de base sur cet ensemble :

-   l'initialiser,

-   y ajouter un élément (si il n'y est pas déjà),

-   savoir combien il y a d'éléments dans l'ensemble,

-   tester si un élément est présent,

-   enlever un élément,

-   libérer les ressources utilisées.

Ci-dessous un exemple d'utilisation où l'on ajoute une suite de mots
(éventuellement en plusieurs exemplaires) et on fait afficher la taille
(qui doit être 10).

~~~C
#include <stdio.h>
#include <stdlib.h>

#include "ens_chaines.h"

int main()
{
    struct ens_chaines ensemble;
    ec_init(& ensemble);

    char *mots[] = {
        "un", "deux", "trois", "un",
        "quatre", "deux", "cinq", "six",
        "sept", "trois", "huit", "neuf",
        "dix", "trois", "sept",
        NULL
    };
    for (int i = 0; mots[i] != NULL; i++) {
        ec_ajouter(& ensemble, mots[i]);
    }

    printf("-> taille %d (attendu = 10)\n",
            ec_taille(& ensemble));
    
    ec_dump(& ensemble);
    ec_liberer(& ensemble);

    return EXIT_SUCCESS;
}
~~~

Le programme affiche également le contenu interne de l'ensemble de
chaînes, ce qui nous facilitera les explications.

    -> taille 10 (attendu = 10)
    0 ->
    1 ->	"trois" (10282497)
    2 ->	"quatre" (170727922)
    3 ->	"un" (2099)
    4 ->	"six" (35140)
    5 ->	"dix" (30805)
    6 ->	"deux" (522598)
    7 ->
    8 ->
    9 ->
    10 ->	"huit" (546666)
    11 ->	"cinq" (518715)
    12 ->	"sept" (596204)
    13 ->
    14 ->	"neuf" (571710)
    15 ->

Nous ne présenterons que quelques opérations, les autres sont laissées
en exercice.

### Idée générale


#### Répartition en alvéoles

-   les chaînes de caractères qui font partie de l'ensemble sont
    réparties dans des "alvéoles".

-   les alvéoles forment un tableau, ce qui permet un accès rapide par
    indice.

-   le numéro de l'alvéole dans laquelle se trouve (ou devrait se
    trouver) une chaîne de caractères est calculé à partir du contenu de
    cette chaîne, par ce qu'on appelle une **fonction de hachage**.

-   plus précisément, le numéro d'alvéole s'obtient comme reste
    (opération modulo) de la division de la valeur du hachage par le
    nombre d'alvéoles.

**Intérêt :** 
La répartition en alvéoles permet de diviser le nombre de comparaisons
nécessaires pour tester la présence d'une chaîne : on ne regarde que
celles présentes dans son alvéole.

**Dans l'idéal,** 
la fonction de hachage serait parfaite, et conduirait à une alvéole où
ne se trouve qu'une chaîne.

**En pratique,** 
on pourra avoir plusieurs chaînes dans certaines alvéoles. On
va donc :

-   prévoir qu'une alvéole contient une `liste` de chaînes,
-   avoir un grand nombre d'alvéoles de façon à avoir statistiquement
    peu de chaînes par alvéole.

### Agrandissement par doublement

La stratégie choisie est de doubler le nombre d'alvéoles quand le nombre
de chaînes présentes dans l'ensemble atteint certain seuil (3/4 du
nombre d'alvéoles). Les chaînes sont alors redistribuées entre les
alvéoles.

Le respect de ce seuil garantit qu'il a au maximum 0.75 chaînes par
alvéole. Il y aura donc peu d'alvéoles avec plus d'une chaîne.

Comme pour les tableaux extensibles, la stratégie de doublement fait
qu'en moyenne chaque alvéole est copiée au plus une fois.

### Doublement et redistribution

Le doublement a une autre propriété intéressante. Quand on redistribue
les chaînes d'une alvéole,

-   soit elles restent dans la même alvéole,

-   soit elles vont dans une alvéole "jumelle" qui vient d'être ajoutée.

**Exemple :**
pour la chaîne `"dix"`, la fonction de hachage vaut 30805.

-   Si il y a 4 alvéoles, elle se trouve dans l'alvéole
    $30805 \ \%\  4 = 1$.

-   En passant à 8 alvéoles, elle va dans la nouvelle alvéole
    $30805 \ \%\  8 = 5 = 4 + 1$.

-   En passant à 16, elle reste en $30805 \ \%\  16 = 5$.

-   En passant à 32, elle va en $30805 \ \%\  32 = 21 =
    16 + 5$.

-   etc.

Ceci nous autorise à redistribuer les chaînes en traitant les anciennes
alvéoles une par une : on est sûr de ne pas avoir à déplacer chaque
chaîne plus d'une fois.

### Détails d'implémentation


#### Sémantique de valeur pour les chaînes

Lorsqu'on appelle la fonction qui sert à ajouter une chaîne, ce qu'on
veut c'est ajouter le contenu de la chaîne. Pour cela on ne peut pas se
contenter de stocker l'adresse de la chaîne reçue, il faut en faire une
copie.

Ci-dessous une erreur classique de programmation en C : si on fait
ensuite afficher le tableau, on s'aperçoit qu'il ne contient pas ce
qu'on pense y avoir mis :

~~~C
  char *joueurs[10];
  char nom[100];
  for (int i=0; i < 10; i++) {
    printf("donnez un nom :");
    scanf("%s", nom);
    joueurs[i] = nom;       // une erreur de débutant
}
~~~

puisqu'on a stocké 10 fois l'adresse de la même variable locale
`nom`...

Lors de l'ajout d'une chaîne, on stocke donc en réalité *une copie*
obtenue par `strdup()`. Cette copie est une ressource appartenant à
l'ensemble, et sera libérée quand

-   on retire une chaîne de l'ensemble

-   on libère l'ensemble

#### Structure des alvéoles

Nous choisissons de représenter les alvéoles, qui en principe ne contiendront que peu d'éléments (moins
de $0.75$ en moyenne), par  des **listes chaînées non
ordonnées**.

### Choix de la fonction de hachage

Une fonction de hachage retourne un nombre non signé, parce qu'elle sert
à calculer un indice (entier positif ou nul) comme reste d'une division entière.

Ce modulo (par une puissance de 2) fait qu'on utilise comme indice les
bits de poids faible de la valeur retournée. Il est important que ces
bits soient, autant que possible, dépendants de tous les caractères de
la chaîne.

Un contre-exemple pour illustrer cette notion. Si le hachage était
calculé ainsi

~~~C
unsigned int hash = 0;
    for (const char *c = chaine; *c != '\0'; c++) {
        hash = 16 * hash + *c;               // mauvais
    }
~~~

à cause du décalage produit par la multiplication par 16, les 4 bits de
droite ne dépendraient que du dernier caractère de la chaîne; les 8 bits
de droite des deux derniers, etc. Les chaînes `"sept"` et `"huit"` se
retrouveraient toujours dans la même alvéole, pour les ensembles qui ont
moins de 256 alvéoles. Idem pour `"six"` et `"dix"`. Et à partir d'une
certaine taille, les premiers octets de la chaîne seront sans influence
sur le résultat (ils seront perdus dans le débordement).

La multiplication par 17 (= 16 + 1) garantit que chaque octet de la chaîne
a une influence sur les bits de poids faible du résultat de la fonction
de hachage.

### Code source


**Entête**

~~~C
// ens_chaines.h

#ifndef ENS_CHAINE_H
#define ENS_CHAINE_H

struct ens_alveole;            // prédéclaration

struct ens_chaines {
    int nb_alveoles;
    int nb_elements;
    struct ens_alveole *alveoles;
};


void ec_init   (struct ens_chaines *e);
void ec_ajouter(struct ens_chaines *e,
		const char *chaine);

int ec_taille  (const struct ens_chaines *e);
void ec_dump   (const struct ens_chaines *e);

void ec_liberer(struct ens_chaines *e);

#endif
~~~

**Code**

~~~C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ens_chaines.h"


struct ens_cellule {
    char * chaine;
    struct ens_cellule *suivant;
};

struct ens_alveole {
    struct ens_cellule *premier;
};


#define NOMBRE_MIN_ALVEOLES 4

void ec_init(struct ens_chaines *e)
{
    e->nb_elements = 0;
    e->nb_alveoles = NOMBRE_MIN_ALVEOLES;
    e->alveoles = malloc(e->nb_alveoles
			 * sizeof (struct ens_alveole));
}

static unsigned int ec_hash(const char * chaine)
{
    unsigned int hash = 0;
    for (const char *c = chaine; *c != '\0'; c++) {
        hash = 17 * hash + *c;
    }
    return hash;
}

static void ec_doubler_nb_alveoles(struct ens_chaines *e)
{
    int na = e->nb_alveoles; // avant agrandissement
    e->nb_alveoles *= 2;
    
    int taille =
	e->nb_alveoles * sizeof (struct ens_alveole); 
    e->alveoles = realloc(e->alveoles, taille);
		

    // initialisation de nouvelles alvéoles
    for (int i = na; i < e->nb_alveoles; i++) {
        e->alveoles[i].premier = NULL;
    }

    // reclassement des éléments des anciennes alvéoles
    for (int i = 0; i < na; i++) {
        struct ens_cellule *premier
	    = e->alveoles[i].premier;
        e->alveoles[i].premier = NULL;
	
        while (premier != NULL) {
            struct ens_cellule *c = premier;
            premier = premier->suivant;
            int num_alveole
		= ec_hash(c->chaine) % (e->nb_alveoles);
	    struct ens_alveole *a
		= &( e->alveoles[num_alveole] );
            c->suivant = a->premier;
            a->premier = c;
        }
    }
}

void ec_ajouter(struct ens_chaines *e, const char *chaine)
{
    int num_alveole = ec_hash(chaine) % (e->nb_alveoles);
    struct ens_alveole * a = &(e->alveoles[num_alveole]);

    // sortie si déjà present
    for (struct ens_cellule *c = a->premier;
	 c != NULL;
	 c = c->suivant) {
        if (strcmp(c->chaine, chaine) == 0) {
            return;
        }
    }

    // Ajout nouvelle cellule avec copie de chaîne
    struct ens_cellule *nc
	= malloc(sizeof (struct ens_cellule));
    nc->chaine = strdup(chaine);
    nc->suivant = a->premier;
    a->premier = nc;
    e->nb_elements += 1;

    // besoin d'agrandir ?
    if (e->nb_elements >= (3 * e->nb_alveoles) / 4) {
        ec_doubler_nb_alveoles(e);
    }
}

void ec_liberer(struct ens_chaines *e)
{
    for (int i = 0; i < e->nb_alveoles; i++) {
        struct ens_cellule *premier
	    = e->alveoles[i].premier;
        while (premier != NULL) {
            struct ens_cellule *c = premier;
            premier = premier->suivant;
            free(c->chaine);
            free(c);
        }
    }
    free(e->alveoles);
    // par précaution 
    e->nb_alveoles = 0;
    e->nb_elements = 0;
    e->alveoles = NULL;
}

int ec_taille(const struct ens_chaines *e)
{
    return e->nb_elements;
}

void ec_dump(const struct ens_chaines *e)
{
    for (int i = 0; i < e->nb_alveoles; i++) {
        printf("%d ->", i);
        for (struct ens_cellule *c = e->alveoles[i].premier;
                c != NULL; c = c->suivant) {
            printf("\t\"%s\" (%u)",
		   c->chaine,
		   ec_hash(c->chaine));
        }
        printf("\n");
    }
}
~~~

[^31]: fini, donné par extension
