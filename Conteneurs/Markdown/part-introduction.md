# Objectifs du document


Ce document montre les principes de fonctionnement de divers
**conteneurs** (tableau extensible, listes chaînées, dictionnaire, ...) en
allant jusqu'aux détails d'implémentation.

Pour aller au niveau le plus bas que permet la portabilité,
l'implémentation est réalisée en C.

Inconvénient du langage C : il ne permet pas la *généricité*.
C'est-à-dire que si on a écrit le code d'un tableau extensible
d'entiers, il faut tout recommencer pour avoir un tableau extensible
de chaînes, par exemple.

Mais l'objectif ici n'est pas d'obtenir une implémentation
"professionnelle" des conteneurs. En pratique on utilisera des
langages de plus haut niveau, ou des bibliothèques existantes, mais ça
ne dispense pas de comprendre comment ça marche.

