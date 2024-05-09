
# Algèbre de Boole et circuits logiques

En combinant les portes logiques, et en prenant garde de ne pas faire de
boucles dans les circuits[^4], on réalise des circuits dont les sorties
ne dépendent que des valeurs des entrées. On pourra alors décrire la
fonction réalisée par ce circuit par sa table de vérité.

L'étude des "tables de vérité" a été entreprise il y a plus d'un siècle,
et constitue ce qu'on appelle l'algèbre de Boole[^5].

Les propriétés de cette algèbre nous permettront de *raisonner* sur les
circuits, et donc de les construire rigoureusement, plutôt que par la
(coûteuse) méthode des essais et erreurs. En particulier nous verrons
des méthodes systématiques pour simplifier les circuits.

## Définitions

On appelle *fonction booléenne* toute fonction de $\{0,1\}^n$ dans
$\{0,1\}$.

Il y a $2^{2^n}$ fonctions booléennes à $n$ variables : en effet la
table de vérité pour décrire d'une fonction booléenne à $n$ variables
contient $2^n$ cases, qui contiennent chacune 0 ou 1.

Une *expression booléenne* est un terme construit à partir de variables
(prises dans un ensemble $V$), de constantes 0 ou 1, et d'opérateurs ET,
OU, et NON. Exemple : $a + \neg(a \cdot \neg{b}) + b$.

Une expression booléenne *représente* une fonction booléenne ; nous
dirons que deux expressions sont équivalentes si elles dénotent la même
fonction.

> **Exemple** Si nous construisons la table de vérité de l'expression
> ci-dessus, et de l'expression $\neg{a}+b$:



| $a$ | $b$ | $\neg{b}$ | $a\cdot\neg{b}$ | $\neg(a\cdot\neg{b})$ | $(\neg{a}\cdot\neg{b}) + b$ | $\neg{a}$ | $\neg{a} + b$ |
|-----|-----|-----------|-----------------|-----------------------|----------------------------|---------|-------------|
| 0   | 0   | 1         | 0               | 1                     | 1                          | 1       | 1           |
| 0   | 1   | 0         | 0               | 1                     | 1                          | 1       | 1           |
| 1   | 0   | 1         | 1               | 0                     | 0                          | 0       | 0           |
| 1   | 1   | 0         | 0               | 1                     | 1                          | 0       | 1           |


>  nous constatons qu'elles coïncident : les deux
> expressions représentent la même fonction.

Par commodité, on appelle *somme* toute expression de la forme
$t_1 + t_2 + \ldots + t_n$. Elle peut se réduire à un seul terme, ou
aucun (dans ce cas c'est 0). Un *produit* est de la forme
$t_1.t_2 \ldots t_n$. Le produit vide est $1$.

Un monôme est un produit de variables ou de négations de variables,
chaque variable n'apparaissant qu'au plus une fois.

> **Exemple de monômes:** $x, \neg{y}, x \cdot \neg{y}\cdot$

L'expression $1$ est également un monome, en tant que produit vide.

> **Remarque** À partir d'un ensemble de $n$ variables on peut
> construire $C^k_n.2^k$ monômes distincts à $k$ variables : pour
> choisir un tel monôme il suffit de sélectionner $k$ variables parmi
> $n$ (d'où le coefficient binomial), et d'attribuer ou non à chacune
> d'entre elles une barre ($2^k$ possibilités).
>
> Il y a en tout $3^n$ monômes, puisqu'il suffit de décider, pour
> chacune des variables, de la faire figurer telle quelle, avec une
> barre, ou pas du tout. Ceci prouve l'égalité:

$$ C^0_n.2^0 +  C^1_n.2^1 + \ldots + C^n_n.2^n$$

> que l'on peut d'ailleurs retrouver en
développant $(1 + 2)^n$ à l'aide des formules connues.


Un monôme est dit *complet* par rapport à un ensemble donné de
variables si toutes les variables de cet ensemble apparaissent une
fois (avec ou sans négation).

Il y a $2^n$ monômes complets sur un ensemble de $n$ variables, chaque
monôme complet correspondant à une des cases d'une table de vérité à
$n$ variables.

Une expression est *en forme canonique* si elle est écrite sous forme
d'une somme sans répétition de monômes complets.

### Proposition

Toute fonction booléenne peut être construite par composition
d'opérations OU, ET et NON.

**Preuve**

Toute fonction booléenne $f(a,b,c\ldots)$ peut être décrite par sa table
de vérité. Chaque case de cette table correspond à un *monôme complet*.
Une expression de la fonction $f$ s'obtient en faisant la somme des
monômes complets dont la valeur est 1.

> **Exemple** Considérons une fonction $maj$ (majorité) à trois
> variables $a,b,c$, qui vaut 1 quand au moins deux des entrées sont à
> un. On dresse la table de vérité de $maj$, en faisant figurer dans la
> marge les monômes correspondants: 

| $a$ | $b$ | $c$ | $maj(a,b,c)$ | monôme                  |
|-----|-----|-----|--------------|-------------------------|
| 0   | 0   | 0   | 0            | $\neg{a}\cdot\neg{b}\cdot\neg{c}$ |
| 0   | 0   | 1   | 0            | $\neg{a}\cdot\neg{b} \cdot c$ |
| 0   | 1   | 0   | 0            | $\neg{a}\cdot b\cdot\neg{c}$ |
| 0   | 1   | 1   | 1            | $\neg{a}\cdot b\cdot c$ |
| 1   | 0   | 0   | 0            | $a\neg{b}\cdot \neg{c}$ |
| 1   | 0   | 1   | 1            | $a\cdot \neg{b}\cdot c$ |
| 1   | 1   | 0   | 1            | $a\cdot b\cdot \neg{c}$ |
| 1   | 1   | 1   | 1            | $a\cdot b\cdot c$ |


et on obtient l'expression en forme canonique (en omettant les points pour le "et") :
 $$maj(a,b,c)=  (\neg a)bc + a(\neg b)c +
 	ab(\neg{c}) + abc$$

## Propriétés des algèbres de Boole

Les opérations ET, OU, NON définies sur l'ensemble $\{0,1\}$ possèdent
les propriétés suivantes: 


|                                     |                                  |                        |
|-------------------------------------|----------------------------------|------------------------|
| $\neg(\neg{A}) = A$                 |                                  | double négation        |
| $\neg{0} = 1$                       | $\neg{1}	= 0$                 | constantes             |
| $\neg{A+B} = \neg{A} \cdot \neg{B}$ | $\neg(A.B)	= \neg{A}+\neg{B}$ | dualité                |
| (A+B)+C = A+(B+C)                   | $(AB)C	= A(BC)$                 | associativité          |
| $A+B =	B+A$                        | $AB	= BA$                       | commutativité          |
| $(A+B)C = AC+BC$                      | $AB+C	= (A+C)(B+C)$             | distributivité         |
| $A+A =	A$                          | $AA	= A$                        | idempotence            |
| $A+0 =	A$                          | $A \cdot 1 = A$                          | éléments neutres       |
| $A+1 =	1$                          | $A \cdot 0 = 0$                          | absorption             |
| $A+\neg{A} =	1$                    | $A \cdot \neg{A} = 0$                    | complémentaires |




**Remarques**

-   Chaque égalité peut-être vérifiée en construisant les tables de
    vérité de ses parties gauche et droite.

-   La colonne de droite contient des équations *duales* de celles de la
    colonne de gauche, obtenues en intervertissant les opérateurs $+$ et $\cdot$, et les constantes 0 et 1.
     On peut passer d'une équation à l'équation duale en utilisant
    seulement $\neg(\neg{A})=A$, $\neg{0}=1$ et
    $\neg(A+B)= \neg{A} \cdot \neg{B}$.

-   On voit assez facilement que ces équations permettent de développer
    n'importe quel terme sous forme d'une expression canonique.
    L'expression canonique d'une fonction étant unique (à la commutation
    de $+$ et $.$ près), ces équations suffisent donc pour montrer
    l'équivalence de deux expressions.

-   Les lois de dualité sont appelées aussi lois de De Morgan.[^6]

### Algèbre de Boole

On appelle *algèbre de Boole* tout ensemble qui possède deux constantes 0
et 1, et des opérations $+,\cdot,\neg$ qui satisfont les équations
ci-dessus.

> **Exercice** Montrez qu'il n'y a pas d'algèbre de Boole à 3 éléments
> $\{0,1,2\}$. 

> Indication : que peut bien valoir $\neg{2}$ ?

On voit facilement que le produit $A \times B$ de deux algèbres de
Boole est également une algèbre de Boole, dont les membres sont des couples.
Les opérations sur les couples sont définies par

- $\neg(a, b)=(\neg{a}, \neg{b})$,
- $(a,b) + (a',b')= (a+a',b+b')$,
- $(a,b) \cdot (a',b') = (a \cdot a',b \cdot b')$. 

Dans le sens inverse, un résultat mathématique (théorème de Stone) dit
que toute algèbre de Boole se ramène en fait à un produit d'algèbres
de Boole à 2 éléments[^7].

## Simplification des expressions

À partir d'une expression booléenne, on pourra facilement fabriquer un
circuit. Pour réaliser une même fonction, on aura tout intérêt à avoir
des circuits qui utilisent le moins possible de portes logiques, pour
des raisons de simplicité, de coût, de taille du circuit et de
consommation de courant.

### Approche  algébrique 

On peut essayer de simplifier les circuits en utilisant les équations
vues plus haut. Par exemple, pour la fonction $maj$ :

$maj(a,b,c) =  \neg{a}bc + a\neg{b}c + ab\neg{c} + abc$

> $=   \neg{a}bc + a\neg{b}c + ab\neg{c} + abc + abc + abc$ (idempotence) 

> $=   \neg{a}bc + abc + a\neg{b}c +abc + ab\neg{c} + abc$ (commutativité)

> $=  (\neg{a}+a)bc  + a(\neg{b}+b)c + ab(\neg{c}+c)$ (distributivité)

> $=   1.bc  + a.1.c + ab.1$ (complémentarité)

> $=   bc  + ac + ab$ (éléments neutres) 

Mais dans ce genre de travail, la difficulté est de mener le calcul
vers une expression simple ... que l'on ne connaît pas a priori.

**Un petit problème mathématique ?** Il existe $2^{2^2}=16$ fonctions
à deux variables.

1. Donnez une expression aussi simple que possible de chacune d'elles. 
2. Déterminez celles qui sont *croissantes*, c'est-à-dire telles que
$x \leq x'$ et $y \leq y'$ entraîne $f(x,y) \leq f(x',y')$. Pour
chacune d'elles, montrez qu'elle peut s'exprimer (sans utiliser de
négation) par une somme de produits de variables.
3. Réciproquement, montrez que toute fonction dont l'expression contient
des ET et des OU (mais pas de NON) est nécessairement croissante.
4. Généralisez au cas des fonctions ayant un nombre quelconque de
variables.

### Méthode de Karnaugh

La méthode de Karnaugh est une méthode visuelle pour trouver une
expression simple d'une fonction booléenne de quelques variables (jusqu'à
6).[^8].

Elle repose sur une présentation particulière de la table de vérité de
la fonction étudiée. Voici la disposition adoptée pour les fonctions de
3 variable $a, b$ et $c$ : 

| a b : c | 0 | 1 |
|---------|---|---|
| **0 0**     |   |   |
| **0 1**     |   |   |
| **1 1**     |   |   |
| **1 0**     |   |   |

et pour 4 variables :

| a b : c d | 0 0 | 0 1 | 1 1 | 1 0 |
|-----------|-----|-----|-----|-----|
| **0 0**   |     |     |     |     |
| **0 1**   |     |     |     |     |
| **1 1**   |     |     |     |     |
| **1 0**   |     |     |     |     |


La disposition est telle que les "coordonnées" de deux cases
adjacentes ne diffèrent que par une seule
variable. Comme chaque case correspond à un monôme complet, un
groupement de 2 cases adjacentes représentera un monôme à $n-1$
variables.

**Exemple :** dans la première table,
- la case en bas à gauche
correspond à $a = 1, b = 0, c= 0$, c'est-à-dire au monôme
$a \cdot \neg b \cdot \neg c$.
- pour sa voisine de droite, c'est le monôme
$a \cdot \neg b \cdot  c$.
- en les regroupant, on obtient 
$a \cdot \neg b \cdot \neg c + a \cdot \neg b \cdot \neg c$
qui est égal à $a \cdot \neg b \cdot ( c + \neg c)$, qui se simplifie en
$a \cdot \neg b$.

**Attention** : il faut également considérer les bords opposés comme étant
adjacents, en regroupant les cases en haut à gauche et en bas à gauche,
on obtient $\neg b \cdot \neg c$.

Les monômes à $n-2$ variables sont visualisés sous forme de carrés, ou
de rectangles $1 \times 4$.

**Exemples** 

-  On a $bd = (a + \neg{a})b(c +\neg{c})d$. En
développant cette expression, on trouve une somme de 4 monômes complets
qui occupent le milieu de la seconde table. 
- Les 4 coins de cette même
table forment (virtuellement) un carré dont l'expression est
> $\neg{a}\cdot\neg{d}$. 
- La colonne de droite correspond à
> $c\cdot \neg{d}$, etc.
- chaque monôme d'une seule variable (sur 4) occupe 8 cases disposées en
rectangles $2 \times 4$.

La méthode de Karnaugh consiste à 

1) écrire la table de vérité de la
fonction dans la table
2) procéder à des regroupements que l'on entoure
3) écrire la somme des monomes correspondants.


##### Algorithme

L'algorithme est le suivant:

> -   Si tous les "1" ont été entourés : arrêter.
>
> -   trouver, visuellement, le plus gros regroupement possible
>     contenant au moins un 1 non entouré.
>
> -   l'entourer sur le tableau, et écrire son expression
>
> -   recommencer

La figure [\[boole1\]](#boole1){reference-type="ref" reference="boole1"}
illustre le déroulement possible de la méthode sur l'exemple de la
fonction majorité. Le résultat obtenu est $BC+AB+AC$.

![Méthode de Karnaugh : exemple[]{label="boole1"}](../Png/boole1.png)

> **Exercice. Le vote :** Une commission est composé d'un président P
> et trois membres A,B,C. Cette commission doit se prononcer sur un
> vote par oui (1) ou non (0) à la majorité. Personne ne peut
> s'abstenir. En cas d'égalité entre les oui et les non, la voix du
> président est prépondérante. En utilisant la méthode de Karnaugh,
> donnez une expression simple de la fonction $vote(A,B,C,P)$.

> **Exercice Décodage 7 segments hexadécimal** Un afficheur 7 segments
> est composé de 7 diodes électro-luminescentes notés a,b,...g (voir
> figure [\[boole2\]](#boole2){reference-type="ref"
> reference="boole2"}). Un nombre est fourni, codé en binaire sur 4 bits
> $x_3x_2x_1x_0$, qui devra être affiché. Donnez l'expression des 7
> fonctions $a(x_3,x_2,x_1,x_0), b(x_3,x_2,x_1,x_0), \ldots$
>
> ![Afficheur 7 segments,
> chiffres[]{label="boole2"}](../Png/boole2.png)

La méthode de Karnaugh est également applicable dans le cas des
fonctions incomplètement spécifiées, c'est-à-dire qui ont des "cases
vides" dans lesquelles on peut mettre ce que l'on veut, parce que cela
correspond à des situations qui ne peuvent pas se produire.

La méthode est alors la suivante: former les plus gros paquets possibles
contenant au moins un 1 non entouré et aucun 0.

> **Exercice Le dé électronique** (fig.
> [\[boole3\]](#boole3){reference-type="ref" reference="boole3"})
> possède trois entrées, par lesquelles arrivent des nombres de 1 à 6
> codés en binaire. Donnez une fonction pour chacune des lampes qui
> indiquera si elle doit être allumée ou éteinte.
>
> ![Le dé électronique[]{label="boole3"}](../Png/boole3.png)

> **Exercice Décodage 7 segments décimal** Reprendre l'exercice de
> l'afficheur 7 segments, en supposant que les valeurs d'entrée vont
> toujours de 0000 à 1001.

> **Exercice Multiples de 3** Proposez un circuit qui prendra en entrée
> un nombre $N$ entre 0 et 15 (codé en binaire évidemment) et dont la
> sortie indiquera si $N$ est un multiple de $3$.


[^4]: les circuits combinatoires (sans boucles) et séquentiels (avec
    boucles) seront étudiés dans les chapitres suivants

[^5]: L'oeuvre la plus célèbre de George Boole (1815-1864) est intitulée
    *Une investigation dans les lois de la pensée, sur lesquelles sont
    fondées les théories mathématiques de la logique et des
    probabilités* (1854), plus connue sous le titre abrégé *Les lois de
    la pensée*

[^6]: Les travaux d'Augustus de Morgan (1806-1871) influencèrent
    fortement George Boole, et ses vives recommandations permirent à ce
    dernier, bien qu'autodidacte, d'obtenir la Chaire de Mathématiques
    du Queen's College de Cork.

[^7]: Ce produit peut être infini, mais c'est une autre histoire

[^8]: Nous ne montrerons ici que la méthode pour 3 et 4 variables, le
    passage à 5 ou 6 variables nécessite une bonne vision dans l'espace
