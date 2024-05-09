Eléments de Technologie
========================

Nous avons vu comment coder l'information par des suites de valeurs
binaires. Nous allons voir maintenant comment représenter ces valeurs
binaires par des signaux électriques afin de les manipuler par des
circuits électroniques.

Représentations de la logique binaire
-------------------------------------

### Représentation des signaux

Il existe plusieurs façons de coder les valeurs 0 et 1. La plus simple,
que nous adopterons dans la suite, est appelée *logique positive* et
consiste à représenter 1 par la présence d'une tension (par exemple +5v)
et 0 par une tension nulle.[^1]

### Génération d'un signal

Il est facile de fournir de tels signaux à un circuit: il suffit d'un
interrupteur à deux positions (utilisé pour les va-et-vient); dans une
position la sortie de l'interrupteur transmettra la tension +V, dans
l'autre 0v (voir figure [\[fig1\]](#fig1){reference-type="ref"
reference="fig1"})

![Génération d'un signal d'entrée[]{label="fig1"}](../Png/fig1.png)

En pratique, on utilise plutôt (figure
[\[fig2\]](#fig2){reference-type="ref" reference="fig2"}) un
interrupteur simple dont la sortie est reliée à une *résistance de
rappel* R assez forte. Lorsque l'interrupteur est fermé (il fat
contact) la sortie est à +V, lorsqu'il est ouvert la résistance ramène
la tension de sortie vers
0. De plus ceci évite d'avoir une entrée "en l'air" quand l'interrupteur
est entre deux positions.

![Génération d'un signal d'entrée
(2)[]{label="fig2"}](../Png/fig2.png)

### Observation d'un signal

Pour observer la sortie d'un circuit on peut utiliser (figure
[\[ampoule\]](#ampoule){reference-type="ref" reference="ampoule"}) une
ampoule du voltage voulu (5v = lampe de poche).

![Ampoule témoin[]{label="ampoule"}](../Png/fig3.png)

On préfèrera généralement employer des diodes électro-luminescentes (LED
= Light Emitting Diode), qui coûtent moins cher et nécessitent un
courant moindre (voir figure
[\[temoin-led\]](#temoin-led){reference-type="ref"
reference="temoin-led"}). 0

![LED témoin[]{label="temoin-led"}](../Png/fig4.png)

Encore mieux, pour éviter de trop "tirer" sur la sortie du circuit
observé, on pourra utiliser un transistor en amplification (voir plus
loin [\[trans-ampli\]](#trans-ampli){reference-type="ref"
reference="trans-ampli"}).

Notions rudimentaires d'électronique
------------------------------------

Quelques notions sommaires d'électronique sont nécessaires pour la
compréhension des circuits logiques de base. Le lecteur est supposé
connaître la loi d'Ohm et des rudiments d'électricité.

### La diode

La diode à semi-conducteurs est un composant électronique muni de deux
bornes: l'*anode* et la *cathode* (voir
[\[diode\]](#diode){reference-type="ref" reference="diode"}).

![La diode: apparence physique et
symbole[]{label="diode"}](../Png/fig7.png)

La propriété fondamentale de la diode est d'opposer qu'une résistance
très faible lorsqu'elle est traversée par un courant de l'anode vers la
cathode (sens passant), et une résistance très forte dans le sens
inverse. Voir figure
[\[diode-on-off\]](#diode-on-off){reference-type="ref"
reference="diode-on-off"}.

![Diodes passante (D1) et bloquée
(D2)[]{label="diode-on-off"}](../Png/fig6.png)

Pour analyser les circuits logiques nous considérerons que les diodes
sont parfaites, c'est-à-dire ayant une résistance nulle dans l'état
passant, et infinie dans l'état bloqué.

> **Remarque importante.** Lorsque nous construirons des circuits nous
> aurons soin d'éviter de faire traverser les diodes par des courants
> trop forts (risque de claquage). Il faudra donc de les monter en série
> avec des résistances pour limiter le courant.

### La diode électro-luminescente

Les diodes électro-luminescentes (LED = Light Emitting Diod, voir fig.
[\[fig9\]](#fig9){reference-type="ref" reference="fig9"}) émettent de la
lumière quand elles sont traversées par un courant de l'ordre de 10 à 20
mA dans le sens passant. Ces diodes offrant une résistance très faible,
il conviendra de les monter en série avec une *résistance limitatrice de
courant* d'une valeur suffisante ($R=U/I=5v/10mA=500
\Omega$).

![LED: apparence physique et schéma[]{label="fig9"}](../Png/fig9.png)

### Le transistor

Le transistor[^2] est un composant à 3 pattes: l'émetteur, le collecteur
et la base (voir figure
[\[transistor\]](#transistor){reference-type="ref"
reference="transistor"}).

![Transistor NPN: boitier, broches (vues de dessous),
schéma[]{label="transnpn"}](../Png/fig8.png)

Dans les montages usuels, le collecteur est relié à la tension
d'alimentation $+V$ au travers d'une résistance $R_c$, l'émetteur étant
relié à la masse (0v). Le courant $I_b$ qui traverse la base permet de
contrôler l'intensité de celui qui traverse l'émetteur et le collecteur.

![Polarisation d'un
transistor[]{label="transistor"}](../Png/fig10.png)

Lorsque le transistor est utilisé en amplification, les courants sont
liés par les équations 

- $I_e = I_c + I_b$
- $I_c = \beta . I_b + I_{ce}$

Les deux constantes $\beta$ et $I_{ce}$ dépendent du transistor: le gain
$\beta$ est de l'ordre de 100, le courant $I_{ce}$ vaut quelques
micro-ampères pour les transistors au silicium, et quelques nano-ampères
pour les transistors au germanium. En général on le néglige pour les
calculs.

Les montages logiques utilisent le mode de fonctionnement
*bloqué-saturé*, en débordant largement de la plage de valeurs où les
formules ci-dessus sont valides: si on applique une tension assez forte
(proche de +V) à la base, l'intensité $I_b$ est maximum et le transistor
n'oppose qu'une résistance très faible entre émetteur et collecteur: le
transistor est saturé. Si on applique une tension nulle à la base, le
courant $I_c$ sera négligeable : le transistor est alors dit bloqué.

[\[trans-ampli\]]{#trans-ampli label="trans-ampli"}

![LED amplifiée par un
transistor[]{label="ampli-diode"}](../Png/fig5.png)

Ceci justifie le montage de la figure
[\[ampli-diode\]](#ampli-diode){reference-type="ref"
reference="ampli-diode"} : lorsque l'entrée est à +V, le transistor est
saturé, donc il laisse passer le courant à travers la LED qui s'éclaire.
Lorsque l'entrée est au niveau bas (0v), le transistor est bloqué et la
LED reste éteinte. En raison des propriétés amplificatrices du
transistor, le courant de base n'a pas besoin d'être très élevé (de
l'ordre de $I_c/\beta$), par conséquent on peut mettre une résistance
limitatrice sur la base. Cette résistance évite de trop "tirer de
courant" du signal que l'on observe, ce qui risquerait de perturber son
fonctionnement.

Portes logiques
---------------

En assemblant ces composants on obtient des *portes logiques* qui
combinent les signaux.

### Porte OU

#### Montage à diodes

Deux diodes et une résistance suffisent pour réaliser une *porte OU*
selon le schéma de la figure
[\[porte-ou\]](#porte-ou){reference-type="ref" reference="porte-ou"}.

![Porte logique OU à diodes[]{label="porte-ou"}](../Png/log1.png)

#### Analyse du montage

Supposons que les deux entrées A et B soient portées au potentiel +V.
Les deux diodes sont dans le sens passant, et laissent donc passer le
courant. Tout se passe alors comme si la sortie S était reliée à la même
tension +V.

Si A et B sont reliées à la masse (0v), les diodes ne conduisent pas le
courant. La sortie S est donc ramené à 0v par la résistance de rappel.

Si une des entrées est à +V et l'autre à la masse, la diode passante
suffit, comme dans le premier cas, à amener la tension +V sur S.

#### Table de vérité de l'opérateur OU

Si nous prenons la convention de logique positive, la tension +V
correspond à la valeur logique "vrai" (notée 1) et 0v à "faux" (0). La
table de vérité de l'opération "$+$" ainsi obtenue est celle de
l'opérateur "OU logique": $

| $A$ | $B$ | $A+B$ |
|---|---|-----|
| 0 | 0 | 0   |
| 0 | 1 | 1   |
| 1 | 0 | 1   |
| 1 | 1 | 1   |



La sortie est à 1 si au moins une des entrées est à 1.

#### Porte OU multiple

En reliant plusieurs entrées de la même façon on obtient une porte OU
multiple. Son fonctionnement se résume en une phrase: la sortie est à 1
si au moins une des entrées est à 1.

Dans les schémas logiques, on représente les portes logiques par un
symbole (figure [\[log2\]](#log2){reference-type="ref"
reference="log2"})

![Symboles des portes OU[]{label="log2"}](../Png/log2.png)

#### Montage à transistors

Le montage de la figure [\[log8\]](#log8){reference-type="ref"
reference="log8"} remplit la même fonction. L'analyse en est laissée au
lecteur.

![Porte OU à transistors en
parallèle[]{label="log8"}](../Png/log8.png)

### Porte ET

#### Montage à diodes

Le schéma (figure [\[log3\]](#log3){reference-type="ref"
reference="log3"}) n'est pas sans rappeler celui de la porte OU.

![Porte ET à diodes[]{label="log3"}](../Png/log3.png)

#### Analyse du montage

Chaque diode ne peut être passante que si l'entrée associée est à 0. Si
une des entrées est à 0, la sortie sera donc également à 0. Par contre
si les deux entrées sont à +V, la sortie S sera à +V au travers de la
résistance de rappel.

#### Table de vérité de l'opérateur ET

L'opération logique "ET" (noté "$\cdot$") correspondant à ce montage
possède donc la table de vérité suivante:


| $A$ | $B$ | $A \cdot B$ |
|---|---|-------------|
| 0 | 0 | 0           |
| 0 | 1 | 0           |
| 1 | 0 | 0           |
| 1 | 1 | 1           |

La sortie est à 1 si les deux entrées sont à 1.

On représente les portes ET (à deux ou plusieurs entrées) par un symbole
(figure [\[log4\]](#log4){reference-type="ref" reference="log4"})

![Symboles des portes ET[]{label="log4"}](../Png/log4.png)

#### Montage à transistors

Le montage de la figure [\[log7\]](#log7){reference-type="ref"
reference="log7"} remplit la même fonction. L'analyse en est laissée au
lecteur.

![Porte ET à transistors en série[]{label="log7"}](../Png/log7.png)

### Porte NON

#### Montage

Dans la figure [\[log5\]](#log5){reference-type="ref" reference="log5"}
on utilise un transistor en mode bloqué/saturé.

![Porte NON à transistor[]{label="log5"}](../Png/log5.png)

#### Analyse du montage

Lorsque l'entrée est au niveau haut, le transistor est saturé. La sortie
est alors reliée à la masse par l'intermédiaire de la résistance interne
très faible du transistor : la sortie S est au niveau bas.

Lorsque l'entrée est au niveau bas, le transistor est bloqué. La
résistance de rappel ramène donc la sortie au niveau haut.

#### Table de vérité  de l'opérateur NON

La table de l'opérateur NON "$\neg$" ainsi obtenu est

| $A$ | $\neg A$ |
|-----|----------|
| 0   | 1        |
| 1   | 0        |

La sortie est à 1 si et seulement si l'entrée est à 0.

On symbolise cet opérateur (figure
[\[log10\]](#log10){reference-type="ref" reference="log10"}) par un
triangle (indiquant par convention l'amplification) suivi d'un rond
(négation).

![Symbole de la Porte NON[]{label="log10"}](../Png/log10.png)

### Porte NON-ET (NAND) 

![Porte NAND[]{label="log9"}](../Png/log9.png)

Le montage de la figure [\[log9\]](#log9){reference-type="ref"
reference="log9"} réalise une fonction dont la table de vérité est:

| $A$ | $B$ | $S$ |
|-----|-----|-----|
| 0   | 0   | 1   |
| 0   | 1   | 1   |
| 1   | 0   | 1   |
| 1   | 1   | 0   |


On remarque aisément que l'on a $S = \neg(A.B)$, et on appelle cet
opérateur le NON-ET (ou "nand").

> **Exercice** Donnez un schéma de cet opérateur utilisant 2 diodes, une
> résistance et un transistor.

On le représente par un symbole "ET" suivi du rond qui indique la
négation (figure [\[log11\]](#log11){reference-type="ref"
reference="log11"}).

![Porte NON-ET[]{label="log11"}](../Png/log11.png)

La porte NAND a un intérêt pratique évident: elle permet de reconstituer
tous les autres types de portes.

-   La porte NON, puisque $\neg A = A \ nand\ 1$

-   La porte ET, puisque $A . B = \neg(A \ nand\ B) =
     (A \ nand\ B) \ nand\ 1$

-   La porte OU, puisque $A + B = \neg(\neg{A} \cdot \neg{B})$
    et donc $A+B= ((A \ nand\ 1) \ nand\ (B \ nand\ 1)) \ nand\ 1$.

### Porte NON-OU (NOR)

La fonction "non-ou" (symbolisée fig.
[\[log14\]](#log14){reference-type="ref" reference="log14"}) est définie
de la même façon, par l'équation $$nor(A,B) = \neg(A + B)$$

  * [ ] ![Symbole de la porte NOR
(non-ou)[]{label="log14"}](../Png/log14.png)

> **Exercice** Proposez une porte NOR à transistors.

### Porte OU-exclusif (XOR)

La fonction XOR "ou-exclusif" (fig.
[\[log15\]](#log15){reference-type="ref" reference="log15"}) est souvent
notée $\oplus$. On la définit par:
$$A \oplus B = (\neg{A} \cdot B) + (A \cdot\neg{B})$$

![Symbole de la porte XOR
(ou-exclusif)[]{label="log15"}](../Png/log15.png)

> **Exercice** Proposez une porte XOR à transistors.

### Le circuit intégré CMOS 4011

Les circuits intégrés logiques sont des boîtiers qui renferment
plusieurs portes logiques inter-connectées. Il existe une grande quantité
de circuits intégrés logiques, renfermant des portes ET, OU, NAND, etc.
Pour des petits montages, il est économique d'utiliser un seul type de
circuit, comme le circuit CMOS 4011, qui contient 4 portes NAND.

#### Brochage

Le circuit 4011 se présente sous forme d'un boîtier DIL (Dual in line) à
14 broches (voir figure [\[log12\]](#log12){reference-type="ref"
reference="log12"}). Une encoche sur le côté gauche permet de
reconnaître le sens du circuit.

![Circuit CMOS 4011 vu de dessus[]{label="log12"}](../Png/log12.png)

Les broches 14 (en haut à gauche) et 7 (en bas à droite) servent à
l'alimentation du circuit (14: +V, 7: masse). Les autres sont les
entrées et sorties des 4 portes NAND:

-   porte 1: entrées 12 et 13, sortie 11;

-   porte 2: entrées 8 et 9, sortie 10;

-   porte 3: entrées 1 et 2, sortie 3;

-   porte 4: entrées 5 et 6, sortie 4;

La figure [\[log13\]](#log13){reference-type="ref" reference="log13"}
montre comment réaliser une porte OU avec ce circuit.

![Porte OU avec CMOS 4011[]{label="log13"}](../Png/log13.png)

> **Exercice Fonctions binaires usuelles** Montrez comment réaliser les
> expressions $A.B$, $A \oplus B$, $A+\overline{B}$ à l'aide d'un
> circuit 4011.

> **Exercice Fonction majorité** Réalisez la fonction $maj(A,B,C)$, dont
> le résultat est 1 si au moins deux entrées sont à 1, à l'aide d'un
> circuit 4011 (ou plusieurs).

> **Exercice** Réalisez la fonction
> $f(A,B,C)= \mbox{si $A=1$ alors $B.C$ sinon $B+C$}$.

#### Conditions d'emploi des circuits CMOS

Les circuits de type CMOS présentent certains avantages pour les
montages expérimentaux:

-   ils acceptent une tension d'alimentation entre 3 et 15 V;

-   leur consommation est très faible (de l'ordre de 0,1 mW par porte);

-   les entrées des circuits CMOS ont une impédance très élevée : on
    peut relier de nombreuses entrées sur la sortie d'une porte sans
    craindre de "tirer" trop de courant de celle-ci.

Par contre, ces circuit sont sensibles à l'électricité statique[^3]. De
plus, la propagation des signaux de l'entrée à la sortie d'une porte est
plus lente (20-40 ns) qu'avec d'autres familles de circuits, comme les
TTL.

#### Emploi des circuits TTL

Les circuits TTL (transistor-transistor-logic) sont très utilisés pour
les réalisations professionnelles. A titre d'exemple, les
caractéristiques de la série SN74 sont:

-   tension nominale d'alimentation de $5v \pm 0.5V$, risque de claquage
    à partir de 7V
-   fonctionnement entre $0$ et $70^oC$
-   puissance par porte de l'ordre de 10 mW
-   courant d'entrée de l'ordre de $1.5 mA$
-   temps de propagation de l'ordre de 10 à 20 ns


[^1]: Une logique *négative* aura des signaux inversés: 0v représente la
    valeur 1, +5v la valeur 0.

[^2]: Pour simplifier l'exposé nous n'évoquerons que les transistors
    NPN.

[^3]: En particulier "effet d'antenne" lorsqu'on approche la main d'un
    circuit dont une des entrées est restée "en l'air"
