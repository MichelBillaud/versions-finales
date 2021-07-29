
Circuits séquentiels
====================

Définition
----------

Un circuit séquentiel possède des entrées E et des sorties S, mais aussi
un état interne Q qui sert à mémoriser de l'information. On peut résumer
un tel circuit par deux fonctions. L'une (fonction de sortie $f$)
indique la valeur des sorties en fonction des entrées et de l'état
actuel :

$$S = f( E , Q )$$

L'autre (fonction de transition $g$) indique l'état que le circuit
prendra à l'instant suivant:

$$Q' = g( E , Q )$$

Du bistable à la bascule RS
---------------------------

Une expérience simple consiste à monter (fig.
[\[seq1\]](#seq1){reference-type="ref" reference="seq1"}) deux portes
NON tête-bêche, la sortie de l'une servant d'entrée à l'autre. Soient
$Q_1$ et $Q_2$ les deux sorties.

![Bistable à deux portes NON[]{label="seq1"}](../Png/seq1.png)

On constate que ce circuit prend l'un des deux eétats suivants:

-   état (0) : $Q_1=0$ et $Q_2=1$

-   état (1) : $Q_1=1$ et $Q_2=0$

et qu'il y reste indéfiniment: on dit que le circuit est *stable*.
(C'est un *bistable*, car il y a deux *positions de stabilité*).

En revanche si on boucle l'entrée avec la sortie d'une seule porte NON,
(fig. [\[seq2\]](#seq2){reference-type="ref" reference="seq2"}) c'est un
circuit *astable* qui oscille continuellement (et très rapidement) entre
0 et 1.

![Circuit astable[]{label="seq2"}](../Png/seq2.png)

Reprenons notre bistable à 2 portes NON. Supposons qu'il soit dans
l'état (0), c'est-à-dire $Q_1=0, Q_2=1$. Pour le faire basculer dans
l'autre état, il faudrait forcer l'entrée E2 à 1. Mais pour l'instant
l'entrée E2 n'est reliée qu'à $Q_1$. On intercale donc (fig.
[\[seq3\]](#seq3){reference-type="ref" reference="seq3"}) une porte OU
avec une entrée de commande S (Set).

![Bistable avec commande S (set)[]{label="seq3"}](../Png/seq3.png)

Dans l'état (0) avec S=0, la situation est stable. L'arrivée d'une
impulsion sur S provoque le passage de E2 à 1, puis $Q_2$ prend la
valeur 0 et $Q_1$ passe à 0. Le bistable est donc dans la situation (1)
qui est stable, et il y reste désormais quel que soit le signal d'entrée
sur S. Ceci est résumé par le chronogramme de la
figure[\[seq4\]](#seq4){reference-type="ref" reference="seq4"}.

![Chronogramme[]{label="seq4"}](../Png/seq4.png)

Pour permettre le retour à l'état (0) on peut ajouter -par symétrie- une
autre entrée de commande R (reset) et une autre porte OU (fig.
[\[seq5\]](#seq5){reference-type="ref" reference="seq5"}).

![Bascule RS: schéma et symbole[]{label="seq5"}](../Png/seq5.png)

Le circuit résultant (que l'on réalise avec des portes NOR) est appelé
*bascule RS*. Son fonctionnement normal se résume comme suit:

-   2 entrées R et S

-   2 sorties $Q_1$ et $Q_2$ (appelées aussi $Q$ et $\overline{Q}$)

-   R et S ne doivent pas être à 1 simultanément.

-   une impulsion sur S met $Q_1$ à 1 et $Q_2$ à 0

-   une impulsion sur R met $Q_1$ à 0 et $Q_2$ à 1

La figure [\[seq6\]](#seq6){reference-type="ref" reference="seq6"}
montre, sous forme de chronogramme, l'effet d'une séquence de "tops"
envoyés successivement sur les entrées de commande d'une bascule RS.

![Chronogramme d'une bascule RS[]{label="seq6"}](../Png/seq6.png)

##### Remarque

Si R et S sont simultanément à 1 les deux sorties sont à 1. Si S et R
repassent simultanément à 0 le résultat est alors imprévisible (dépend
des vitesses de réaction des différentes portes).

Bascules dérivées
-----------------

### Bascule RS à portes NAND

En mettant des portes NAND au lieu des portes NOR, on obtient une
bascule RS à signaux de commande inversés. On désigne alors les entrées
de commande par $\overline{R}$ et $\overline{S}$ (voir figure
[\[seq7\]](#seq7){reference-type="ref" reference="seq7"}).

![Bascule RS à portes NAND[]{label="seq7"}](../Png/seq7.png)

### Bascule RS avec horloge

Les commandes R et S ne sont actives que lorsque l'entrée d'horloge est
à 1. Il suffit (fig. [\[seq8\]](#seq8){reference-type="ref"
reference="seq8"}) de valider les signaux R et S par l'entrée H au moyen
de deux portes ET.

![Bascule RSH: schéma et symbole[]{label="seq8"}](../Png/seq8.png)

### Bascule D

On la réalise à partir de la bascule RSH (figure
[\[seq9\]](#seq9){reference-type="ref" reference="seq9"}) Lorsque son
entrée H est à 1, elle mémorise la valeur de son entrée D. Quand H=0,
elle reste insensible aux changements sur D (voir chronogramme de la
figure [\[seq10\]](#seq10){reference-type="ref" reference="seq10"})

![Bascule D[]{label="seq9"}](../Png/seq9.png)

![Chronogramme d'une Bascule D[]{label="seq10"}](../Png/seq10.png)

La bascule D est utilisée pour la constitution des *mémoires*.

La conception de circuits séquentiels
-------------------------------------

Considérons par exemple une commande d'éclairage par bouton-poussoir. Il
y a une entrée B (l'état du bouton : appuyé ou pas), une sortie L (la
lampe allumée ou éteinte), mais il est clair que la sortie ne dépend pas
seulement de l'entrée, mais aussi de ce qui s'est passé avant, que l'on
représente par un état Q.

Ici on pourra décider que Q mémorise simplement l'état de la lampe. Si
Q=0, la lampe est éteinte. Si Q=1, la lampe est allumée

La sortie est fonction de l'entrée et de l'état $$L = f( B , Q )$$

Ici on prendra par exemple $L=Q$.

Une autre fonction indique comment l'état interne évolue au cours du
temps. Pour simplifier le raisonnement on découpe le temps en
"instants". L'état Q' "à l'instant suivant" dépend des entrées ainsi que
de l'ancien état: $$Q' = g(B , Q)$$ Dans l'exemple on dira que si B=0
l'état reste stable et si B=1 l'état s'inverse, d'où la table:

$$\begin{array}{|cc|l|}
\hline
	B & Q &	Q'=g(B,Q) \\
\hline
	0 & 0 &	0 \\
	0 & 1 &	1 \\
	1 & 0 &	1 \\
	1 & 1 &	0 \\
\hline
\end{array}$$

A partir de là on pourrait en conclure qu'il suffit (fig.
[\[seq11\]](#seq11){reference-type="ref" reference="seq11"}) d'une
bascule D pour représenter l'état, qui serait activée par B et dont la
sortie serait rebouclée sur l'entrée à travers un NOT.

![Un montage naïf[]{label="seq11"}](../Png/seq11.png)

Mais attention ça ne marche pas ! En effet l'impulsion sur le bouton
dure "plusieurs instants", ce qui fait clignoter (trop vite pour que
l'oeil le perçoive) la sortie pendant l'appui du bouton : c'est un état
instable. La vitesse élevée d'oscillation fait alors qu'à la fin de
l'impulsion le résultat est imprévisible.

Pour s'en sortir on emploiera le montage de la figure
[\[seq12\]](#seq12){reference-type="ref" reference="seq12"}, (appelé
maître-esclave).

![Bascule RSH maître-esclave[]{label="seq12"}](../Png/seq12.png)

la bascule 1 (maître) est validée par $H_1=B$ et la 2 (esclave) par
$H_2=\overline{B}$, mais on utilise (et c'est là toute l'astuce) une
porte NON dont le seuil de déclenchement est plus bas que la normale, ce
qui fait qu'une impulsion sur B correspond à deux impulsions décalées
sur $H_1$ et $H_2$, comme le montre le chronogramme de la figure
[\[seq13\]](#seq13){reference-type="ref" reference="seq13"}.

![Seuils de déclenchement[]{label="seq13"}](../Png/seq13.png)

Donc à l'arrivée d'une impulsion (front montant) la bascule esclave se
verrouille en mémorisant l'état du maître, puis le maître change d'état.
A la fin de l'impulsion (front descendant de l'impulsion sur B) le
maître se verrouille, et l'esclave change d'état.

> **Exercice** : vérifier le fonctionnement de ce circuit à l'aide d'un
> chronogramme (dessiner l'arrivée de 2 impulsions sur B).

> **Problème Bascule JK** En utilisant le même principe (maître-esclave)
> concevoir une bascule JK. Comme son nom l'indique une bascule JK
> possède 3 entrées J,K et H et deux sorties $Q$ et $\overline{Q}$. La
> bascule ne peut changer d'état que pendant une impulsion sur H. Si
> J=K=0 l'état reste inchangé. Si J=1 K=0 l'état devient 1. Si J=0 et
> K=1 l'état devient 0. Si J=K=1 l'état s'inverse.

##### Circuits Synchrones

On appelle *circuit synchrone* un circuit séquentiel dont l'état interne
ne change qu'à l'arrivée d'une impulsion sur une entrée spéciale appelée
"Horloge". On suppose en général que les autres signaux ne varient pas
pendant l'arrivée d'un top d'horloge.

L'intérêt de cette horloge est de donner une définition précise de
"l'instant suivant". C'est l'horloge qui rythme les transitions d'état.

Application à la synthèse de compteurs
--------------------------------------

On appelle *compteur* un dispositif séquentiel qui passe périodiquement
par une suite d'états. Par exemple le compteur binaire sur deux bits
suivra la séquence $00, 01, 10 , 11, 00, 01,
10, 11, 00$, etc. à chaque top d'horloge.

Nous allons voir comment réaliser, de manière systématique, n'importe
quel compteur, d'abord avec des bascules D maître-esclave, puis avec des
bascules JK qui permettent d'obtenir des circuits plus simples.

### Réalisation à l'aide de bascules D

> **Exemple compteur binaire 2 bits**
>
> Les deux bits de l'état sont stockés dans deux bascules D.
>
> -   il n'y a pas de signal en entrée
>
> -   les sorties $Q_1, Q_0$ sont issues directement des bascules D
>
> -   pour réaliser la fonction de transition, il suffit de présenter
>     sur les entrées D1 et D0 la valeur du prochain état que l'on
>     calculera à partir de $Q_1$ et $Q_0$. Pour cela on construit la
>     table: $$\begin{array}{|cc|cc|}
>     \hline 
>     \multicolumn{2}{|c|}{	\mbox{ancien} } &
>     \multicolumn{2}{c|}{	\mbox{nouvel}} \\
>     \multicolumn{2}{|c|}{	\mbox{état} } &
>     \multicolumn{2}{c|}{	\mbox{état}} \\
>     \hline
>     	Q_1 & Q_0 &	D1 & D0 \\
>     \hline
>     	0 &  0 &	0 &  1 \\
>     	0 &  1 &	1 &  0 \\
>     	1 &  0 &    	1 &  1 \\
>     	1 &  1 &	0 &  0 \\
>     \hline
>     \end{array}$$ D'où on tire facilement : $$\begin{array}{rcl}
>     	D1 &=& Q_1 \oplus  Q_0 \\
>     	D0 &=& \overline{ Q_0}
>     \end{array}$$
>
### Réalisation à l'aide de bascules JK

Le principe est légèrement différent : à partir de l'ancien état nous ne
faisons plus calculer le nouvel état pour l'injecter dans les bascules,
mais nous déterminons les commandes à envoyer aux bascules (sur les
entrées J et K) pour que l'état change.

Avant de reprendre l'exemple du compteur 2 bits, quelques remarques sur
les bascules JK. Regardons la table de transition :
$$\begin{array}{|c|cc||c|}
\hline 
\mbox{ancien}	&  &  & \mbox{nouvel} \\
\mbox{état}	& J & K & \mbox{ état} \\
\hline
	0 &	0 &  0 &	0 \\
	0 &	0 &  1 &	0 \\
	0 &	1 &  0 &	1 \\
	0 &	1 &  1 &	1 \\
	1 &	0 &  0 &	1 \\
	1 &	0 &  1 &	0 \\
	1 &	1 &  0 &	1 \\
	1 &	1 &  1 &	0 \\
\hline	
\end{array}$$

En regardant cette table d'une façon différente, on obtient
$$\begin{array}{|cc|c|}
\hline 
\multicolumn{2}{|c|}{\mbox{pour passer}} &
\mbox{il faut} \\
\mbox{de} & \mbox{à} & \mbox{avoir} \\
\hline
	0 &	0 &	J=0 \\
	0 &	1 &	J=1 \\
	1 &	0 &	K=1 \\
	1 &	1 &	K=0 \\
\hline
\end{array}$$

Ceci va nous servir pour construire le compteur 2 bits, à l'aide de 2
bascules JK.

$$\begin{array}{|cc|cc|cc|}
\hline
\multicolumn{2}{|c|}{\mbox{ancien}} &
\multicolumn{2}{c|}{\mbox{nouvel}} &
\multicolumn{2}{c|}{\mbox{commandes}}  \\
\multicolumn{2}{|c|}{\mbox{état}} &
\multicolumn{2}{c|}{\mbox{état}} &
\multicolumn{2}{c|}{\mbox{à envoyer}} \\
	Q_1 &Q_0&	Q'_1& Q'_0& & \\	
\hline
	0&  0&	0&   1&	J_1=0 &J_0=1 \\
	0&  1&	1&   0&	J_1=1 &K_0=1  \\
	1&  0&    1&   1&	K_1=0 &J_0=1  \\
	1&  1&	0&   0&	K_1=1& K_0=1  \\
\hline
\end{array}$$

Il ne reste plus qu'à trouver des expressions convenables pour
$J_0,K_0,J_1$ et $K_1$ en fonction de $Q_1$ et $Q_0$. En remplissant les
tableaux de Karnaugh : $$\begin{array}{|r|cc|}
\hline
J_0(Q_0,Q_1) & 0 & 1 \\
\hline
0 & 1 & . \\
1 & 1 & 1 \\
\hline
\end{array}
\hspace{0.5cm}
\begin{array}{|r|cc|}
\hline
K_0(Q_0,Q_1) & 0 & 1 \\
\hline
0 & . & 1 \\
1 & . & 1 \\
\hline
\end{array}$$ $$\begin{array}{|r|cc|}
\hline
J_1(Q_0,Q_1) & 0 & 1 \\
\hline
0 & 0 & 1 \\
1 & . & . \\
\hline
\end{array}
\hspace{0.5cm}
\begin{array}{|r|cc|}
\hline
K_1(Q_0,Q_1) & 0 & 1 \\
\hline
0 & . & . \\
1 & 0 & 1 \\
\hline
\end{array}$$ L'abondance de cas indéterminés nous permet d'obtenir des
expressions très simples: $J_0 = 1$, $K_0 = 1$, $J_1= Q_1$, $K_1= Q_1$.

> **Exercice compteur modulo 3** La séquence à effectuer est
> $00,01,10,00,01,10$, etc.

> **Exercice compteur binaire sur 3 bits**
> $000, 001, 010, 011, ... 111,000,...$

> **Exercice Compteur modulo 10** Séquence
> 0000,0001,\....,1000,1001,0000\...

> **Exercice Compteur/décompteur 3 bits** Une entrée supplémentaire C
> indique s'il faut compter (C=1) ou décompter (C=0).

> **Exercice Compteurs rampants** 0000, 1000, 1100, 1110, 1111, 0111,
> 0011, 0001, 0000, \....

> **Exercice Compteurs de gray**
>
> -   sur 1 bit: 0,1,0,1\...
>
> -   sur 2 bits: 00,01,11,10,00,\....
>
> -   sur 3 bits: 000,001,011,010,110,111,101,100,\...
>

