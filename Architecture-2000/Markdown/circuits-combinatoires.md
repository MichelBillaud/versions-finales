
# Quelques circuits combinatoires


Dans ce chapitre nous étudions brièvement quelques circuits
combinatoires qui interviennent dans la réalisation des composants
logiques d'un ordinateur.

Nous présenterons l'étude de ces circuits sous une forme commune : la
*spécification* énonce rapidement le rôle du circuit, la *fonction de
tranfert* indique précisément (en général par des tables de vérité) la
valeur des sorties pour toutes les entrées possibles, la *réalisation*
montre un des circuits possibles.

## Demi-additionneur


### Spécification

C'est un circuit (voir fig. [\[combi1\]](#combi1){reference-type="ref"
reference="combi1"}) à deux entrées $a, b$ et deux sorties $r, s$. Les
entrées représentent les nombres 0 et 1, et $rs$ est l'expression en
binaire de leur somme. ($s$ est la somme, $r$ la retenue).

![Demi-additionneur[]{label="combi1"}](../Png/combi1.png)

### Fonction de transfert

**Table**

| a | b | r  s |
|---|---|------|
| 0 | 0 | 0  0 |
| 0 | 1 | 0  1 |
| 1 | 0 | 0  1 |
| 1 | 1 | 1  0 |

**Équations**

- $r = a \cdot b$
- $s = a \cdot \neg b + b \cdot \neg a = a \oplus b$

### Réalisation:

Le schéma de la figure [\[combi2\]](#combi2){reference-type="ref"
reference="combi2"} se déduit immédiatement des équations.

![Schéma d'un demi-additionneur[]{label="combi2"}](../Png/combi2.png)

## Additionneur élémentaire

Le demi-additionneur que nous venons de voir ne suffit pas pour réaliser
des additions "chiffre par chiffre" parce qu'il produit des retenues,
mais ne sait pas les utiliser.

### Spécification

L'*additionneur élémentaire* (Fig.
[\[combi3\]](#combi3){reference-type="ref" reference="combi3"}) est un
circuit à 3 entrées $a,b,c$ et deux sorties $r,s$. Le nombre $rs$
indique, en binaire, le nombre d'entrées qui sont à 1.

![Additionneur[]{label="combi3"}](../Png/combi3.png)

### Fonction de transfert

| a b c   | r  s |
|---------|------|
| 0  0  0 | 0  0 |
| 0  0  1 | 0 1  |
| 0  1  0 | 0 1  |
| 0  1  1 | 1 0  |
| 1  0  0 | 0 1  |
| 1  0  1 | 1 0  |
| 1  1  0 | 1 0  |
| 1  1  1 | 1 1  |

**Équations** :

- $r =  a\cdot b + b \cdot c +a\cdot c$
- $s =  a \oplus b \oplus c =  a \cdot b \cdot c + \neg{a}\cdot b \cdot c + a \cdot \neg b \cdot c + a \cdot b \cdot \neg c$

> **Exercice** Montrez qu'un additionneur peut être réalisé à partir de
> trois demi-additionneurs

> **Exercice** Montrez qu'un additionneur peut être réalisé à partir de
> deux demi-additionneurs et une porte OU.

## Circuit additionneur $2 \times n$ bits


En mettant côte à côte $n$ additionneurs on peut réaliser un
additionneur $n$ bits.

### Spécification

Circuit à $2n+1$ entrées ($a_0 \ldots a_{n-1},
b_0 \ldots b_{n-1}, c$) et $n+1$ sorties ($s_0 \ldots s_{n-1},r$). Les
entrées $a_{n-1}a_{n-2}\ldots a_1 a_0$ représentent un nombre A codé en
binaire (et de même pour B sur les entrées $b_j$), et $c$ est la retenue
entrante. Les sorties $rs_{n-1}s{n-2}\ldots s_1 s_0$ expriment la valeur
de $A+B+c$.

### Réalisation

Une réalisation directe (par étude des tables de vérité et recherche
d'expressions minimales) n'est envisageable que pour de très petites
valeurs de n (si n = 3 il y a 7 entrées, donc des tables de vérité à 128
cases ...).

On procède donc par décomposition du problème : il suffit de mettre en
parallèle n additionneurs élémentaires identiques. La figure
[\[combi4\]](#combi4){reference-type="ref" reference="combi4"} montre un
additionneur $2 \times 4$ bits.

![Additionneur en tranches[]{label="combi4"}](../Png/combi4.png)

> **Remarque** Ces additionneurs "en tranches" peuvent eux-mêmes être
> juxtaposés pour former des additionneurs capables de traiter des
> nombres plus grands : il suffit de relier la retenue sortante de
> chaque circuit à la retenue entrante du suivant.

## Décodeur simple

### Spécification

Ce circuit possède $n$ entrées $a_0 \ldots a_{n-1}$ et $2^n$ sorties
$s_0 \ldots s_{{2^n}-1}$. Les entrées $a_i$ codent un nombre $A$ en
binaire. La sortie $s_A$ est mise à 1, les autres à 0.

#### Fonction de transfert

Pour un circuit à 2 entrées, $n=2$, on a la table : 

| $a_1$  $a_0$ | $s_0$  $s_1$  $s_2$  $s_3$ |
|--------------|----------------------------|
| 0 0          | 1 0 0 0                    |
| 0 1          | 0 1 0 0                    |
| 1 0          | 0 0 1 0                    |
| 1 1          | 0 0 0 1                    |


#### Réalisation

On voit facilement qu'à chaque sortie correspond un monôme complet sur
$a_0, a_1\ldots$, et réciproquement. Voir figure
[\[combi5\]](#combi5){reference-type="ref" reference="combi5"} pour le
schéma d'un décodeur "2 vers 4".

![Décodeur "2 vers 4"[]{label="combi5"}](../Png/combi5.png)

> **Exercice Dessinez un décodeur "3 vers 8"**

## Décodeur avec validation 

Ce décodeur possède une entrée supplémentaire V, qui sert à "activer" le
circuit. Si cette entrée est à 1, le décodeur fonctionne comme
précédemment. Si $V=0$, toutes les sorties sont à 0.

On obtient (fig. [\[combi6\]](#combi6){reference-type="ref"
reference="combi6"}) ce circuit par une simple modification du schéma
précédent.

![Décodeur "2 vers 4" avec
validation[]{label="combi6"}](../Png/combi6.png)

> **Remarque** Les décodeurs avec validation peuvent être assemblés
> entre eux pour former des décodeurs plus gros. Le montage de la figure
> [\[combi7\]](#combi7){reference-type="ref" reference="combi7"} montre
> un décodeur "maître" pilotant 4 décodeurs esclaves, le tout formant un
> décodeur "4 vers 16" avec validation.

![Montage de décodeurs en
maître-esclaves[]{label="combi7"}](../Png/combi7.png)

> **Exercice** Quelles doivent être les valeurs des entrées pour avoir
> $s_{13} = 1$ ?

# Multiplexeur

Autre circuit très utile, le multiplexeur permet de sélectionner une
*entrée*, pour la reporter sur la sortie. C'est un circuit à une seule sortie S. Il prend
comme entrées un nombre $N$ sur k bits, et $2^k$ entrées $e_i$. La
valeur de la $N$-ième entrée est copiée sur la sortie S.

![Multiplexeur 4 voies[]{label="combi8"}](../Png/combi8.png)

La figure [\[combi8\]](#combi8){reference-type="ref" reference="combi8"}
montre un multiplexeur 4 voies. On remarquera que le multiplexeur
contient un décodeur 2 vers 4.

> **Exercice Multiplexeur 16 voies** Montrez comment réaliser un
> multiplexeur 16 voies par un montage maître-esclaves.

## Exercices


### Test d'égalité

Concevoir un circuit qui prendra en entrée deux nombres binaires A et B
de 4 chiffres, et indiquera si ces deux nombres sont égaux.

### Comparateur

Concevoir un circuit qui prendra en entrée deux nombres binaires A et B
de 4 chiffres, et indiquera si $A<B$, $A=B$ ou $A>B$. Essayez d'obtenir
un circuit "cascadable" pour comparer des nombres plus grands.

### Additionneur à retenue anticipée

Dans l'additionneur classique la retenue se propage de chiffre en
chiffre, ce qui induit un délai de calcul proportionnel au nombre N de
bits des nombres à traiter. Evaluez ce délai en fonction de N et du
temps de traversée des portes ET, NON, OU.

La première retenue sortante $r_0$ vaut $a_0b_0 + a_0c_0 + b_0c_0$
($c_0$ est la première retenue entrante). Pour la seconde retenue on a
$r_1 = a_1b_1 + a_1c_1 + b_1c_1$. Comme $c_1=r=0$, on peut donc exprimer
$r_1$ en fonction de $a_0,a_1,b_0,b_1,c_0$ (donnez la formule). C'est ce
qu'on appelle le *pré-calcul* de $r_1$. Or cette formule s'exprime avec
deux étages de portes (faites le schéma).

En suivant la même technique, donnez une formule pour $r_2$, puis $r_3$.
Que dire du temps de traversée d'un tel additionneur N bits ? Quelle est
la contrepartie de ce gain de temps ?

### Compteur

Réaliser un circuit à 3 entrées $e_1,e_2,e_3$ et 2 sorties $s_0,s_1$. Le
nombre binaire $s_1s_0$ indiquera le nombre d'entrées qui sont à 1.

### Encodeur de priorités

Réaliser un circuit à 3 entrées $e_1,e_2,e_3$ et 2 sorties $s_0,s_1$. Le
nombre binaire $s_1s_0$ indiquera le plus grand indice des entrées qui
sont à 1, ou $00$ si toutes les entrées sont à 0.
