
Algèbre de Boole et circuits logiques
=====================================

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

Définitions
-----------

On appelle *fonction booléenne* toute fonction de $\{0,1\}^n$ dans
$\{0,1\}$.

Il y a $2^{2^n}$ fonctions booléennes à $n$ variables: en effet pour
décrire une fonction booléenne à $n$ variables il suffit de remplir les
$2^n$ cases de sa table de vérité, chaque case pouvant contenir 0 ou 1.

Une *expression booléenne* est un terme construit à partir de variables
(prises dans un ensemble $V$), de constantes 0 ou 1, et d'opérateurs ET,
OU, et NON. Exemple : $a + \overline{a . \overline{b}} + b$.

Une expression booléenne *représente* une fonction booléenne ; nous
dirons que deux expressions sont équivalentes si elles dénotent la même
fonction.

> **Exemple** Si nous construisons la table de vérité de l'expression
> ci-dessus, et de l'expression $\overline{a}+b$:
> $$\begin{array}{|cc|ccc||c||c||c|}
> \hline
> a &b & \overline{b}& a.\overline{b}& \overline{a.\overline{b}} & 
>   \overline{a.\overline{b}} + b & \overline{a} & \overline{a}+b \\
> \hline
> 0 & 0  & 1 & 0 & 1 & 1 & 1 & 1\\
> 0 & 1  & 0 & 0 & 1 & 1 & 1 & 1\\
> 1 & 0  & 1 & 1 & 0 & 0 & 0 & 0\\
> 1 & 1  & 0 & 0 & 1 & 1 & 0 & 1\\
> \hline
> \end{array}$$ nous constatons qu'elles coïncident : les deux
> expressions représentent la même fonction.

Par commodité, on appelle *somme* toute expression de la forme
$t_1 + t_2 + \ldots + t_n$. Elle peut se réduire à un seul terme, ou
aucun (dans ce cas c'est 0). Un *produit* est de la forme
$t_1.t_2 \ldots t_n$. Le produit vide est $1$.

Un monôme est un produit de variables ou de négations de variables,
chaque variable n'apparaissant qu'au plus une fois.

> **Exemple de monômes:** $x, \overline{y}, x.\overline{y}.z, 1$

> **Remarque À** partir d'un ensemble de $n$ variables on peut
> construire $C^k_n.2^k$ monômes distincts à $k$ variables : pour
> choisir un tel monôme il suffit de sélectionner $k$ variables parmi
> $n$ (d'où le coefficient binomial), et d'attribuer ou non à chacune
> d'entre elles une barre ($2^k$ possibilités).
>
> Il y a en tout $3^n$ monômes, puisqu'il suffit de décider, pour
> chacune des variables, de la faire figurer telle quelle, avec une
> barre, ou pas du tout. Ceci prouve l'égalité:
> $$\sum_{k=0}^n C^k_n.2^k = 3^n$$ que l'on peut d'ailleurs retrouver en
> développant $(1 + 2)^n$ à l'aide des formules connues.

Un monôme est *complet* par rapport à un ensemble donné de variables si
toutes les variables de cet ensemble apparaissent une fois. Il y a $2^n$
monômes complets sur un ensemble de $n$ variables, chaque monôme complet
correspondant à une des cases d'une table de vérité à $n$ variables.

Une expression est *en forme canonique* si elle est écrite sous forme
d'une somme sans répétition de monômes complets.

##### Proposition

Toute fonction booléenne peut être construite par composition
d'opérations OU, ET et NON.

##### Preuve

Toute fonction booléenne $f(a,b,c\ldots)$ peut être décrite par sa table
de vérité. Chaque case de cette table correspond à un *monôme complet*.
Une expression de la fonction $f$ s'obtient en faisant la somme des
monômes complets dont la valeur est 1.

> **Exemple** Considérons une fonction $maj$ (majorité) à trois
> variables $a,b,c$, qui vaut 1 quand au moins deux des entrées sont à
> un. On dresse la table de vérité de $maj$, en faisant figurer dans la
> marge les monômes correspondants: $$\begin{array}{|ccc|c|l}
> \cline{1-4}
> a & b & c & maj(a,b,c) & \mbox{mon\^ome} \\
> \cline{1-4}
> 0 & 0 & 0 & 0 & \overline{a}\overline{b}\overline{c} \\
> 0 & 0 & 1 & 0 & \overline{a}\overline{b}c \\
> 0 & 1 & 0 & 0 & \overline{a}b\overline{c} \\
> 0 & 1 & 1 & 1 & \overline{a}bc \\
> 1 & 0 & 0 & 0 & a\overline{b}\overline{c} \\
> 1 & 0 & 1 & 1 & a\overline{b}c \\
> 1 & 1 & 0 & 1 & ab\overline{c} \\
> 1 & 1 & 1 & 1 & abc \\
> \cline{1-4}
> \end{array}$$ et on obtient l'expression en forme canonique
> $$maj(a,b,c)=  \overline{a}bc + a\overline{b}c +
> 	ab\overline{c} + abc$$

Propriétés des algèbres de Boole
--------------------------------

Les operations ET, OU, NON définies sur l'ensemble $\{0,1\}$ possèdent
les propriétés suivantes: $$\begin{array}{rclrcll}
 \overline{\overline{A}} &=& A& &&	& \mbox{double négation} \\
\overline{0} &=& 1	& \overline{1}	&=& 0	& \mbox{constantes} \\
\overline{A+B} &=& \overline{A}.\overline{B}	&
\overline{A.B}	&=& \overline{A}+\overline{B}	& 
\mbox{dualité} \\
(A+B)+C &=& A+(B+C)	&
(AB)C	&=& A(BC)	& \mbox{associativité} \\
A+B &=&	B+A & AB	&=& BA	& \mbox{commutativité} \\
(A+B)C &=& AC+BC &
AB+C	&=& (A+C)(B+C)	& \mbox{distributivité} \\
A+A &=&	A & AA	&=& A	& \mbox{idempotence} \\
A+0 &=&	A & A.1 &=& A	& \mbox{éléments neutres} \\
A+1 &=&	1 & A.0 &=& 0	& \mbox{absorption} \\
A+\overline{A} &=&	1 & A.\overline{A} &=& 0	
& \mbox{complémentaires} \\
\end{array}$$

##### Remarques

-   Chaque égalité peut-être vérifiée en construisant les tables de
    vérité de ses parties gauche et droite.

-   La colonne de droite contient des équations *duales* de celles de la
    colonne de gauche, obtenues en intervertissant $+$ et $\cdot$, 0 et
    1. On peut passer d'une équation à l'équation duale en utilisant
    seulement $\overline{\overline{A}}=A$, $\overline{0}=1$ et
    $\overline{A+B}= \overline{A}.\overline{B}$.

-   On voit assez facilement que ces équations permettent de développer
    n'importe quel terme sous forme d'une expression canonique.
    L'expression canonique d'une fonction étant unique (à la commutation
    de $+$ et $.$ près), ces équations suffisent donc pour montrer
    l'équivalence de deux expressions.

-   Les lois de dualité sont appelées aussi lois de De Morgan.[^6]

#### Algèbre de Boole

On appelle *algèbre de Boole* tout ensemble qui possède deux éléments 0
et 1 et des opérations $+,\cdot,\neg$ qui satisfont les équations
ci-dessus.

> **Exercice** Montrez qu'il n'y a pas d'algèbre de Boole à 3 éléments
> $\{0,1,2\}$. (Indication : que vaut $\overline{2}$ ?).

On voit facilement que le produit $A \times B$ de deux algèbres de
Boole est également une algèbre de Boole. Les opérations sur le
produit sont définies par
$\overline(a,b)=(\overline{a},\overline{b})$, $(a,b) + (a',b') =
(a+a',b+b')$, $(a,b).(a',b') = (a.a',b.b')$. 

Dans le sens inverse, un
résultat mathématique (théorème de Stone) dit que toute algèbre de
Boole se ramène en fait à un produit d'algèbres de Boole à 2
éléments[^7].

Simplification des expressions
------------------------------

À partir d'une expression booléenne, on pourra facilement fabriquer un
circuit. Pour réaliser une même fonction, on aura tout intérêt à avoir
des circuits qui utilisent le moins possible de portes logiques, pour
des raisons de simplicité, de coût, de taille du circuit et de
consommation de courant.

On peut essayer de simplifier les circuits en utilisant les équations
vues plus haut. Par exemple, pour la fonction $maj$ :
$$\begin{array}{rcll}
	maj(a,b,c)&=& \overline{a}bc + a\overline{b}c + ab\overline{c} + abc \\
&=&  \overline{a}bc + a\overline{b}c + ab\overline{c} + abc + abc + abc &
\mbox{(idempotence)} \\
&=&  \overline{a}bc + abc + a\overline{b}c +abc + ab\overline{c} + abc &
\mbox{(commutativité)} \\
&=&  (\overline{a}+a)bc  + a(\overline{b}+b)c + ab(\overline{c}+c) &
\mbox{(distributivité)} \\
&=&  1.bc  + a.1.c + ab.1 & \mbox{(complémentarité)} \\
&=&  bc  + ac + ab & \mbox{(éléments neutres)} 
\end{array}$$

Mais la difficulté est alors de mener le calcul vers une expression
simple que l'on ne connaît pas a priori.

> **Problème** Donnez une expression aussi simple que possible de
> chacune des $2^{2^2}=16$ fonctions à deux variables.
>
> Déterminez celles qui sont croissantes, c'est à dire telles que
> $x \leq x'$ et $y \leq y'$ entraîne $f(x,y) \leq f(x',y')$. Pour
> chacune d'elles montrez qu'elle peut s'exprimer (sans utiliser de
> négation) par une somme de produits de variables.
>
> Réciproquement, montrez que toute fonction dont l'expression contient
> des ET et des OU mais pas de NON est nécessairement croissante.
>
> Généralisez au cas des fonctions ayant un nombre quelconque de
> variables.

Méthode de Karnaugh
-------------------

La méthode de Karnaugh est une méthode visuelle pour trouver une
expression simple d'une fonction booléenne de quelques variables (jusqu'à
6).[^8].

Elle repose sur une présentation particulière de la table de vérité de
la fonction étudiée. Voici la disposition adoptée pour les fonctions de
3 et 4 variables:

$$\begin{array}{|r|cc|}
\cline{1-3}
ab\ c&  0 & 1 \\
\cline{1-3}
00 & & \\
01 & & \\
11 & & \\
10 & & \\
\cline{1-3}
\end{array}
\hspace{.5in}
\begin{array}{|r|cccc|}
\cline{1-5}
ab\ cd&  00 & 01 & 11 & 10 \\
\cline{1-5}
00 & & &&\\
01 & & &&\\
11 & & &&\\
10 & & &&\\
\cline{1-5}
\end{array}$$

On remarque que dans ces tables, deux cases adjacentes ne diffèrent que
le changement de valeur d'une seule variable. Comme chaque case
correspond à un monôme complet, un groupement de 2 cases adjacentes
représentera un monôme à $n-1$ variables.

> **Exemple** Les deux cases du bas de la première table correspondent
> respectivement à $a\overline{b}\overline{c}$ et $a\overline{b}c$, qui
> diffèrent par la variable $c$. En les regroupant on obtient
> $a\overline{b}\overline{c} + a\overline{b}c = a\overline{b}(\overline{c}+c)
> = a\overline{b}$

Attention : il faut également considérer les bords opposés comme étant
adjacents, par exemple les cases $\overline{a}\overline{b}\overline{c}$
(en haut à gauche) et $a\overline{b}\overline{c}$ (en bas à gauche) se
regroupent en $b\overline{c}$.

Les monômes à $n-2$ variables sont visualisés sous forme de carrés, ou
de rectangles $1 \times 4$.

> **Exemple** On a $bd = (a + \overline{a})b(c +\overline{c})d$. En
> développant cette expression on trouve une somme de 4 monômes complets
> qui occupent le milieu de la seconde table. Les 4 coins de cette même
> table forment (virtuellement) un carré dont l'expression est
> $\overline{a}\overline{d}$. La colonne de droite correspond à
> $c\overline{d}$, etc.

De même les produits de $n-3$ variables occupent 8 cases disposées en
rectangles $2 \times 4$.

La méthode de Karnaugh consiste à écrire la table de vérité de la
fonction dans la table, puis procéder à des regroupements que l'on
entoure et dont on écrit l'expression au fur et à mesure.

##### Algorithme

L'algorithme est le suivant:

> -   Si tous les 1s ont été entourés : arrêter.
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

> **Exercice Le vote** Une commission est composé d'un président P et
> trois membres A,B,C. Cette commission doit se prononcer sur un vote
> par oui ou non à la majorité. Personne ne peut s'abstenir. En cas
> d'égalité entre les oui et les non, la voix du président est
> prépondérante. En utilisant la méthode de Karnaugh, donnez une
> expression simple de la fonction $vote(A,B,C,P)$.

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
