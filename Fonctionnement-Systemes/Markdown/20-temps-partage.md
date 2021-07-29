
#  Tâches et processus

On appelle **processus**, ou **tâche**, un programme qui est *en cours
d'exécution* sous le contrôle du système d'exploitation. 

Ce cours s'intéresse aux systèmes **multi-tâches** 
qui font tourner plusieurs processus présents en mémoire en même
temps. De nos jours, ces systèmes multi-tâches sont présents dans tous
les ordinateurs grands et petits (smartphones).[^2]. 

On parlera indifféremment de multi-tâches ou de "temps partagé" (*time
sharing*), même si les puristes réservent ce dernier terme aux systèmes
multi-utilisateurs.

[^2]: Les systèmes mono-tâches existent dans les petits dispositifs
    d'informatique embarquée qui ne font qu'une chose à la fois. Par
    exemple une centrale météo qui relève la température, la pression,
    etc.  et transmet les données périodiquement à un serveur.
	



## Problématique des systèmes multi-tâches

Un système multi-tâches "fait tourner" plusieurs processus à la fois,
même sur une machine qui n'a qu'un seul processeur, grâce la technique
de "temps partagé" (*time slicing*).

En réalité, le processeur fait avancer chaque tâche pendant pendant un
petit laps de temps (de l'ordre de 10-100ms), puis passe à la
suivante, etc. Ce laps de temps étant très court, ceci donne, à notre
échelle, une *illusion* d'avancement simultané, tout comme la
projection rapide d'images fixes successive donne une illusion de
continuité.


Comme plusieurs processus sont présents, il se pose plusieurs
problèmes :

- contrôler l'usage des périphériques par les processus,
- partager équitablement le temps,
- partager la mémoire disponible entre les processus, pour éviter
que l'un accède à l'espace mémoire de l'autre




## Programmation dans un langage de haut niveau

Pour pouvoir faire tourner des programmes écrits dans des langages de
haut niveau, il faut que les compilateurs convertissent les appels aux
"fonctions système" en appels à une bibliothèque "runtime"
d'exécution, qui fera les appels systèmes en se conformant à l'**ABI**
(*Application Binary Interface*) du système, c'est-à-dire aux conventions
fixées pour les numéros de service, les registres utilisés etc.


# Le fonctionnement multi-tâches : partage du temps

La notion d'interruption permet de voir l'ordinateur comme un "système
réactif", dont l'état évolue par exécution des instructions, mais qui
répond aussi à l'arrivée d'évènements extérieurs.


## Table des processus

La table des processus est une structure de données centrale d'un
système d'exploitation.

Elle contient la description des divers processus présents en mémoire, avec pour chacun :

- son état (en cours d'exécution ? bloqué ?...)
- un bloc de contexte qui sauvegarde le contenu des registres,
- une description de l'espace mémoire qu'il utilise,
- son propriétaire, les droits dont il dispose,
- etc.

## États d'un processus

Situation banale : vous avez plusieurs fenêtre ouvertes à l'écran.
Dans un navigateur web, vous cliquez sur un lien, qui tarde à
répondre.  Vous en profitez pour continuer à faire autre chose dans
une autre fenêtre.


**Que s'est-il passé ? **

-  En cliquant sur le lien, le navigateur a envoyé (via la couche
réseau) une requête HTTP, et il s'est mis en attente d'une réponse.
- Mais il ne passe pas son temps à surveiller activement l'arrivée de
cette réponse.
- Au contraire, le navigateur (ou du moins le processus qui s'occupe
de l'onglet) est **bloqué** jusqu'à l'arrivée de la réponse (ou
l'expiration d'un délai jugé trop long).

Maintenant, le système peut activer une des autres tâches présentes.

**Que se passe-t-il ensuite ?**

- Lorsque la carte réseau reçoit un paquet, elle signale au système
  d'exploitation qu'une trame est arrivée est arrivé.
- le système d'exploitation (la pile TCP/IP) examine cette trame, en
extrait un paquet IP, constate que c'est un paquet TCP, et qu'il fait
partie d'une connexion ouverte par le navigateur.
- le contenu du paquet est donc transmis au navigateur web, qui est
débloqué, et pourra alors traiter la réponse.


## États et transitions

On voit donc 3 états possibles pour les processus


- **actif** : le processeur est en train d'exécuter une des
  instructions de la tâche,
- **bloqué** : la tâche ne peut pas être activée, elle attend un
événement pour pouvoir continuer,
- **prêt** : la tâche n'est pas bloquée, elle pourrait être
  activée.

Des changements d'état ont lieu, sous le contrôle du 
système d'exploitation :

1. Un processus **actif** appelle un service
qui prend du temps (par exemple, aller chercher des données
sur un disque). Le processus est alors mis à l'état **bloqué**.
2. Lorsque la réponse arrive (interruption), le processus demandeur
qui est **bloqué** est mis à l'état **prêt** (il se peut aussi que le
processus qui est **actif** à ce moment là soit mis à l'état
**prêt**).
3. Quand un processeur/coeur est libre, le système choisit un des
   processus **prêts** pour le rendre **actif**.

~~~
                ACTIF 
              ^     _\
             /        \
 activation	/	       \  envoi
		   /            \ requête
		  /				 v
	  PRÊT  <--------- BLOQUÉ
               requête
			   terminée
~~~


Ceci entraîne des **commutations de contexte**

- quand on processus **sort** de l'état actif, dans lequel un
processeur exécutait ses instructions, le contenu des registres du
processeur est sauvé dans le "bloc de contexte" du processus

Quand un processus est **activé**, les informations du 
bloc de contexte sont placées dans les registres, et l'exécution
reprend là où elle en était arrêtée.

## Exercices


**TODO**.

Reprendre quelques classiques, pour montrer

- qu'on peut profiter des temps morts d'une tâche pour en faire
avancer une autre
- qu'on y gagne en rendement (par rapport à l'exécution des tâches en
  séquence)

Par exemple tâches qui font quelques cycles calcul/entrée sortie.


Voir aussi cohabitation de tâches "IO-bound" et "CPU-bound".


## Temps partagé

Avec le système expliqué ci-dessus, si un processus ne fait que du
calcul et aucun appel système (par exemple parce que le programmeur a
fait une boucle sans fin), il reste actif et donc monopolise la
machine indéfiniment.

On souhaite évidemment éviter cette situation, que l'on retrouvait
dans les systèmes d'exploitation à "**ordonnancement coopératif**"
(MacOs jusqu'à la version 9, Windows jusqu'à 3.11),, dans lesquels on
compte sur la bonne volonté et la compétence des programmeurs
d'application pour que tout se passe bien.



### Utilisation d'un timer

La solution est d'utiliser un **timer** (circuit d'horloge) qui émet
une interruption au bout d'un certain temps (typiquement 20-100 ms).

Ce timer

- est armé (programmé pour un certain délai) quand un processus
est activé
- interrompt le processus actif à échéance du délai (*timeout*).

Le processus actif est alors mis à l'état **prêt**, et un autre
processus prêt est choisi pour être activé.


~~~
                ACTIF 
              ^     _\
             //       \
 activation	//	       \  envoi
		   // timeout   \ requête
		  /v			 v
	  PRÊT  <--------- BLOQUÉ
               requête
			   terminée
~~~

Ainsi, on évite que le "temps de processeur" soit monopolisé par un
programme qui boucle (ou qui calcule très longtemps).


### Choix du quantum de temps

On appelle "quantum" la durée accordée à un processus actif
avant qu'il soit interrompu par le timer. Compromis à trouver :

- si il est long, les processus qui "mangent du temps de calcul" vont
"charger" la machine et laisser aux autres processus peu d'occasions
d'être activés.
- si il est court, le système d'exploitation sera sollicité plus
souvent, et consommera une part plus importante du temps. Les
commutations de contexte ont un coût....

Dans la mesure où c'est très dépend de ce qu'on donne à faire à la
machine, solution pragmatique : essayer, mesurer, ajuster.

## Politiques d'ordonnancement

Il reste un petit détail à régler concernant l'**ordonnancement**, 
c'est-à-dire la manière de choisir un processus prêt pour l'activer,
sachant qu'il peut y en avoir plusieurs.

On peut imaginer plusieurs façons de faire. On les compare sur des
critères

- de sûreté (le fait que tous les processus avancent),
- d'équitabilité,
- d'efficacité (profiter au maximum des ressources),
- ...

qui dans la réalité sont évidemment contradictoires.


### Tourniquet (*first-in, first-out*)

- Les processus prêts forment une file d'attente. 
- Choix du processus le plus ancien de la file.

Sûr et équitable, mais ne permet pas d'avoir
des processus plus prioritaires que d'autres.


### Niveaux de priorité fixes

- On affecte à chaque processus un niveau de priorité. À chaque niveau
  correspond une file d'attente.
- On active le processus le plus ancien de la file la plus prioritaire.

Efficace, mais risque : si les processus du niveau le plus élevé
bouclent, situation de **monopole** ou de **coalition** qui empêche
les autres processus de s'exécuter.


### Niveaux de priorité variable

- la priorité d'un processus varie au cours du temps. La priorité d'un
processus qui arrive au bout de son quantum baisse. Elle remonte quand
il demande des entrées-sorties.

Les tâches courtes sont favorisées, ce qui est agréable pour
l'utilisation interactive. Quand un calcul se met à durer, il devient
moins prioritaires.

Problème : deux processus qui bouclent en communiquant par un pipe
conservent une priorité élevée.


### Classes de processus

(Multi-level feedback queues)

- On définit plusieurs files d'attente.
- On choisit "aléatoirement" une file dont on active le processus le
  plus ancien.

En pondérant (par exemple files choisies à 70%, 20% et 10%) on
favorise certains processus, sans risque de monopole.

## Résumé

Les systèmes multi-tâches, inventés à la fin des années 50, ont été
rendus possibles pratiquement par l'introduction dans les processeurs
de divers dispositifs matériels : interruptions, modes, protection
mémoire, etc.

Dans la machine, un seul programme peut être actif à la fois, par
processeur.  Dans le système d'exploitation, les programmes présents
en mémoire sont répertoriés dans une table des processus, qui contient
leur état (actif, prêt, bloqué), et les informations nécessaires pour
pouvoir les "activer".

L'état des processus change par le biais des interruptions :

- quand ils provoquent des exceptions,
- lors d'un appel système (interruption logicielle), qui peut conduire
  à la fin d'un processus ou son blocage,
- à la fin d'un quantum de temps (interruption horloge), sur les systèmes
modernes qui sont *préemptifs*, 
- à l'arrivée d'un évènement extérieur (interruption matérielle)
attendu par un processus bloqué (qui redevient prêt).


Lorsqu'un processeur se libère, l'ordonnanceur (*scheduler*) choisit,
parmi les processus qui sont prêts, celui qui sera activé.

Ce choix se fait selon une politique d'ordonnancement où
rentrent en compte divers facteurs, parmi lesquels l'équitabilité, des
priorités voulues, l'impossibilité de monopoliser les processeurs,
etc.



## Glossaire

- **Actif** : état d'un processus, indique qu'un des processeurs
est en train d'exécuter ses instructions.
- **Bloc de contexte** : structure de données du système qui contient
les informations (contenu des registres, adresse en mémoire....) qui
permettront de faire reprendre l'exécution d'un processus là où en
était arrêté.
- **Bloqué** : état d'un processus qui attend un évènement
extérieur pour pouvoir continuer son exécution.
- **Coopératif** : type de système d'exploitation multi-tâche dans
lequel les programmes doivent être écrits de façon à ne pas
monopoliser le processeur.
- **Commutation de contexte** : sauvegarde / restauration du contexte
du processus actif (registres, ...) dans le "bloc de contexte" du
processus (dans la table des processus).
- **État** d'un processus : Voir Actif, Prêt, Bloqué
- **Multi-tâche** : se dit d'un système d'exploitation qui permet
d'exécuter plusieurs programmes en donnant une illusion de
simultanéité. Voir Préemptif et Coopératif.
- **Multi-traitement** : se dit d'un système d'exploitation
où plusieurs programmes peuvent être présents en mémoire
- **Ordonnanceur** : composant d'un système d'exploitation qui
choisit, quand un processeur est libre, un processus à l'état prêt
pour l'activer.
- **Préemptif** (système multi-tâches) : lors de l'activation d'une tâche,
arme une horloge qui l'interrompra automatiquement après un certain délai (quantum).
- **Prêt** : état d'un processus qui continuera son exécution quand
il sera activé par l'ordonnanceur.
- **Processus** : abstraction qui décrit "un programme en cours d'exécution".
- **Quantum** : dans un système multitâche préemptif, le délai (de
l'ordre de 10-100ms) au terme duquel le processus actif est
automatiquement interrompu pour (éventuellement) activer un autre processus.
- **Scheduler** : voir *ordonnanceur*.
- **Table des processus** : structure de données du système qui contient les informations relatives aux processus : état, bloc de contexte, droits d'accès, etc.
- **Tâche**, voir processus.
- **Temps partagé** : voir système d'exploitation *multi-tâche*.





# Le partage de l'espace

Dans la mémoire de l'ordinateur vont se retrouver
le code et les données des processus, ainsi que
du système d'exploitation.

Comment se répartir cet espace, et surtout le protéger
contre les erreurs des programmes ?



## Linéaire
 
Dans un système mono-tâche, le système d'exploitation est chargé au
démarrage (typiquement au fond de la mémoire), et y reste jusqu'à
l'arrêt de la machine.  Et les programmes d'applications sont
ensuite chargés au début de l'espace restant.

En passant à un système multi-tâches, on peut imaginer placer les
programmes d'applications les uns après les autres. Chaque programme
occupera une plage d'adresses (adresse de début / adresse de fin)

### Allocation/libération

Comme les programmes apparaissent et disparaissent au gré des
chargements et fin d'exécution, le système tient une comptabilité des
espaces disponibles.

Le chargement d'un programme sera possible uniquement si on peut lui
allouer un espace suffisamment grand pour le loger. Mais 
il ne suffit pas que le total
des espaces libre excède la taille du programme, il faut aussi que cet espace
soit contigu (en un seul morceau), 

Exemple : on a chargé successivement des programmes A, B, C, D de
tailles respectives 20, 10, 20, 30 KiB dans une mémoire de 64 KiB.  Les
programmes A et C se terminent, ce qui laisse 40 KiB octets
disponibles. Mais on ne pourra pas lancer un programme de 25KiB, parce
que le plus grand bloc libre est de 20 KiB seulement. La mémoire est trop
**fragmentée**.

Le **mécanisme** d'**allocation** consiste à chercher un bloc assez grand
pour y loger le programme. Diverses stratégies sont possibles :

- la plus simple **first fit** consiste à regarder les blocs libres dans
l'ordre des adresses, et de prendre le premier qui soit assez
grand. Ce bloc libre est découpé, entre la partie qui est allouée, et
le reste qui est remis dans la liste de blocs libres.
- la stratégie **best fit** est légèrement meilleure. Elle consiste
à prendre le plus petit bloc qui soit assez grand, ce qui évite d'entamer
de grands blocs quand on peut faire avec les petits.

Dans tous les cas, lors de la **libération**, le bloc qui se libère
est fusionné si possible avec les blocs libres voisins pour en former
un plus gros.




**Exercice** : La stratégie *best-fit* est une heuristique[^7] qui ne
résout pas complètement le problème. Trouvez des scénarios (suite
d'allocations et de libérations) pour lesquels

1.  *first-fit* réussit, alors que *best-fit* échoue,
2. l'inverse.



[^7]: technique susceptible de fournir une solution approchée à un
    problème (mais pas toujours).

### Une idée pour la protection : registres limite

Lorsqu'un programme d'application s'exécute, le matériel doit 
l'empêcher d'accéder à autre chose que son propre espace mémoire.

Une solution simple est d'équiper le processeur de "registres limite"
dans lesquels le système mettra les adresses de début et de fin de cet
espace. Des comparateurs[^8] connectés aux registres et au bus d'adresse
détecteront toute tentative d'accéder en dehors de cette plage, et
déclencheront une interruption "accès mémoire illégal".

Ces registres ne sont manipulables qu'en mode privilégié.

**En pratique**, cette idée a été peu utilisée.  En effet, a priori
les programmes d'applications peuvent être chargés n'importe où, en
fonction de ce qui a été chargé avant. Or les programmes contiennent
des instructions de branchements, avec des adresses calculées à la
compilation. Il devient compliqué de charger des programmes qui
contiennent des adresses absolues. De même si on veut les déplacer
pour "dé-fragmenter" la mémoire.


### Autre idée : espace logique

Une idée plus intéressante est de considérer que chaque processus
dispose d'un espace mémoire, qu'il voit à travers des "**adresses
logiques**" qui - pour lui- commencent à 0.

Cet espace logique correspond à une plage d'**adresses physiques**.
En additionnant une adresse logique et l'adresse de début de la plage,
on obtient l'adresse physique correspondante.

Dans le processeur on intègre quelques circuits pour effectuer la
**génération d'adresses** physiques  :

- un registre "base" qui contient l'adresse physique de début de la
  plage,
- un additionneur qui calcule une adresse physique en ajoutant
le contenu de ce registre les adresses logiques produites par le
programme en cours d'exécution.

et pour la **protection** :

- un registre qui contient la taille de la plage,
- un comparateur entre ce registre et l'adresse logique, qui lève une
  interruption en cas de débordement.

Ceci introduit une distinction conceptuelle entre deux espaces
d'adressage :

-  "espace logique", avec des adresses logiques qui vont de 0 à
taille-1. Ces adresses logiques sont internes au processeur.
-  "espace physique", avec des adresses physiques qui vont de base à
   base + taille - 1. Ces adresses sont utilisées pour les accès à la
   mémoire.


### Déplacement des programmes en mémoire

Cette indépendance permet au système d'exploitation de déplacer un
programme, en copiant ailleurs son "image mémoire" et en faisant
pointer le registre de base vers le nouvel emplacement. C'est une
stratégie curative pour le problème de **fragmentation**.

Malheureusement, c'est une opération qui prend du temps.

Et on doit aussi le faire quand un programme demande à disposer de
plus d'espace mémoire pendant son exécution[^9], alors que son espace
mémoire est suivi par un autre espace occupé.


## Espace paginé

Une approche radicalement différente apporte une solution à ces problèmes,
et conduira à la notion de "mémoire virtuelle" (voir plus loin).


### Pages et cadres 

**Découpage de l'espace logique** : L'espace logique d'un processus
est maintenant considéré comme une succession de "pages" de même
taille (une puissance de 2, dépendant de l'architecture de la
machine).

**Par exemple**, sur une machines à pages de 4Kib ($2^12 = 4094$), un
processus de 10354 octets occupe 3 pages. La page 0 correspond aux
adresses logiques 0 à 4095, la page 1 aux adresses de 4096 à 8191, et
la page 2, qui n'est pas complètement occupée, de 8192 à 12287.

Calculer le calcul du numéro de page correspondant à une adresse
logique n'est pas compliqué : c'est le quotient de l'adresse logique
(par exemple 9876) par la taille de page (4096), soit 2. Et le reste 
donne l'**offset** (position dans la page).

Aucun circuit de calcul n'est nécessaire : l'offset est dans les 12
bits de droite de l'adresse, le numéro de page dans les bits de gauche.

~~~
                            binaire            décimal
---------------------  ------------------    ----------
              adresse  0010 0110 1001 0100   = 9876 
       numéro de page  0010                  = 2
position dans la page       0110 1001 0100   = 1688
~~~


**L'espace d'adressage physique** est, de la même façon, découpé en 
"cadres" (de page) la même taille[^11].

Bien évidemment, les pages logiques correspondront à des cadres.

### Table de pages, génération d'adresses


La correspondance est assurée par un groupe de registres appelé
**table des pages**, qui fait partie de la MMU (**memory management
unit**), un composant du processeur.

Ces registres établissent une correspondance entre 

- le numéro de page extrait d'une adresse logique,
- le numéro du cadre qui contient cette page.


**Exemple**, avec une table des pages qui contient

| page | cadre |
| --   | --    |
| 0    | 4     |
| 1    | 10    |
| 2    | 3     |

l'adresse logique 5100, qui est à la position 1006 de la page 1,
(parce que $5100 = 1 \times 4096 + 1006$) se trouve en mémoire à la
position 1006 du cadre 10 (qui correspond à la page 1), soit l'adresse
physique $10 \times 4096 + 1006 = 41966$.


La table est consultée à chaque accès à la mémoire pour générer
l'adresse physique. Pour un accès rapide (en temps élémentaire),
elle utilise un indexage matériel (multiplexage,
registres associatifs...).

La table est chargée par le système d'exploitation quand un processus
est activé. Dans la table des processus, on trouve donc une copie
de la table des pages du processus.


### Possibilité de partage

Les tables de page permettent d'avoir des espaces mémoires communs à
plusieurs processus. Exemple, avec les tables de pages ci-dessous,
les processus P1 et P2 ont tous deux accès aux octets du cadre n°6,

~~~
P1      P2
---     ---     
0 4     0 1
1 2     1 0
2 6     2 3
        3 6
~~~

mais ils ne le voient pas avec les mêmes adresses logiques.


**Note** : les droits d'accès à des pages communes peuvent être
différents. Pour faire respecter ces droits d'accès, la MMU contiendra
aussi des indicateurs de permissions (lire, modifier, faire exécuter).

# Mémoire virtuelle

Si on observe ce qui se passe dans la machine, on constate qu'en fait
la plupart des pages qui ont été chargées ne sont pas "actives". Par
exemple, le début d'un programme a été chargé et exécuté, et on ne
revient pas dessus ensuite.

Qui plus est, les adresses utilisées par un processus sur une courte
période de temps sont souvent voisines les unes des autres (principe
de **localité**).

Ce qu'on appelle l'**ensemble de travail**, c'est-à-dire les pages
dont se sert effectivement un processus à un moment donné, est
nettement plus petit que l'espace d'adressage du processus.

On peut donc envisager de retirer les pages inactives de la mémoire,
pour faire de la place à d'autres programmes. 

Mais a priori, on ne sait pas si une page inactive 
va resservir dans le futur ou pas. Une idée naturelle est donc
de les sauvegarder sur disque[^13], pour pouvoir les récupérer au
besoin.

Ceci conduit à la notion de **mémoire virtuelle**, qui contient à la
fois les pages présentes en mémoire centrale (**mémoire réelle**), et
celles qui ont été sauvegardées sur disque.

Nous allons voir maintenant comment la conjonction du matériel et du
système d'exploitation permet de donner aux programmes l'illusion
qu'ils fonctionnent comme en mémoire, mais dans un espace qui est
beaucoup plus grand.


## Principe

**Matériel**

- la MMU contient une table des pages **présentes en mémoire réelle**,
- quand le programme utilise une page dont le numéro n'y figure pas,
la MMU produit une interruption "défaut de page"[^14], ce qui active
une routine du système d'exploitation.

**Le système d'exploitation**

- bloque alors le processus qui était en cours d'exécution,
- trouve un cadre de page disponible,
- va chercher la page manquante sur le disque

Quand cette page finit par arriver (le disque est un périphérique
relativement lent) :

- le système copie la page dans ce cadre,
- ajuste la table des pages du processus,
- et le remet à l'état prêt.


Le principe est donc relativement simple. La difficulté est de trouver
un cadre de page disponible. Quand toute la mémoire est occupée, il
faut "sortir" une page présente (*paging out*) pour pouvoir ramener
(*paging in*) celle dont le processus a besoin. 



## Éviction : critères

Les performances de la machine dépendront de la qualité de
l'**algorithme d'éviction** utilisé pour choisir la page présente que
l'on va remplacer.

Les facteurs qui rentrent en compte

- Il faut éviter d'évincer une page dont on va avoir bientôt besoin,
- On ne peut pas prédire l'avenir, mais il est probable qu'une page
   récemment utilisée le sera encore prochainement (principe de
   localité).
- Sauvegarder une page sur disque prend du temps.
- Si une page avait été chargée depuis le disque, et n'a pas été
modifiée depuis en mémoire réelle, il est inutile de la sauvegarder.

Et donc : les pages qui n'ont pas servi depuis longtemps et/ou qui
n'ont pas été modifiées depuis longtemps sont de "bons candidats"
pour l'éviction.


## Déterminer l'âge des pages, stratégie LRU


Une petite modification de la MMU permet de connaître les pages
qui n'ont pas été utilisées depuis longtemps.

Un indicateur R est ajouté pour chaque page, il indique si
la page a été accédée (R = referenced).


- le bit R est mis à 0 au départ,
- il passe à 1 quand il y a un accès en lecture ou écriture.

Et dans les tables du système, un entier est aussi ajouté pour coder l'"âge"
de chaque page :

- l'âge est initialisé à 0 quand la page est chargé en mémoire réelle,
- Périodiquement, le système interroge la MMU. Si le bit R d'une page
  est à 0, son âge est incrémenté, sinon il revient à 0. Les bits R
  sont tous remis à 0 ensuite.

Ceci permet de mettre en place la stratégie dite "LRU" (*least recently
used*) où on choisit d'évincer une des pages les plus âgées, qui n'a
pas servi depuis longtemps.


## Trouver les pages non-modifiées

Dans la MMU, on ajoute un bit M (M = *modified*) pour chaque page.

- ce bit est mis à 0 lors du chargement de la page,
- il passe à 1 chaque fois que le processus modifie quelque chose dans
  la page.

Il indique donc si la page a été modifiée depuis son chargement.

Le système interrogera la MMU pour récupérer la liste des pages
modifiées.

En prenant en compte cette information, on obtient une stratégie du
type :

> choisir une des pages les plus âgées, non modifiée de préférence


**Exercice**: Dans la littérature, on trouve une version de cette
stratégie sous le nom "NRU" (*not recently used*). Elle n'utilise que
les bits R et M, et pas l'âge. Ces bits définissent 4 classes de
pages. Dans quel ordre sont-elles choisies ?


## Résumé

La **mémoire virtuelle** permet une meilleure utilisation de la mémoire
primaire, en libérant la place occupée par les pages inactives.

Les pages inactives sont transférées (évincées) en mémoire secondaire,
d'où elles peuvent être récupérées en cas de besoin (défaut de page
détecté par la MMU lors de la génération d'adresses).


Les échanges entre mémoires primaire et secondaire étant lents, la
qualité de l'algorithme d'éviction (choix d'une page à sauvegarder
pour la remplacer par une autre qui est nécessaire) est
primordiale. Ces algorithmes se basent essentiellement sur deux
considérations

- une page qui n'a pas été modifiée depuis son chargement en mémoire
primaire n'a pas besoin d'être sauvegardée ;
- les pages dont on aura besoin prochainement sont probablement
celles qui ont été référencées récemment (principe de localité).

Il est donc préférable de choisir d'évincer une page qui n'a été
référencée depuis longtemps, et qui n'a pas été modifiée.


Note: lorsqu'une machine est "chargée" avec des processus qui n'ont
pas ce comportement "local", les défauts de page devient trop
nombreux, et les transferts entre mémoire primaire et secondaire
deviennent un goulot d'étranglement qui cause un **écroulement**
des performances (**thrashing**).

##  Glossaire

- **Défaut de page** : se produit quand la MMU détecte qu'une adresse
logique ne correspond pas à un cadre de page présent en mémoire
primaire.
- **Écroulement du système** (ou *thrashing*), se produit quand les
  défauts de page générés par les processus provoquent un trafic
  trop important entre mémoires primaire et secondaire.
- **Ensemble de travail** (*working set*), les pages utilisées par un
processus pendant un certain temps. En raison du principe de localité,
cet ensemble peut être nettement plus petit que l'espace d'adressage.
- **Espace d'adressage** d'un processus : les adresses valides 
que manipule un processus.
- **Éviction** : choix du cadre de page dans lequel charger
la page manquante lors du traitement d'un défaut de page. Voir LRU.
- **Génération d'adresses** : détermination (par le circuit MMU) de
  l'adresse physique qui correspond à une adresse logique.
- **Localité** (principe de) : énonce que l'exécution d'un processus
met en jeu, le plus souvent, des accès à des adresses logiques
voisines. 
- **LRU** (least recently used), heuristique pour l'éviction de pages
dans un système à pagination.
- **Mémoire paginée** :  technique consistant à découper l'espace logique
d'adressage d'un processus en **pages**, la mémoire réelle en **cadres**
de page, la correspondance étant établie par une table des pages.
- **Mémoire primaire** : les "barrettes mémoire" d'un ordinateur.
- **Mémoire secondaire** : dispositif (en général une partition d'un disque)
ou sont sauvegardées les pages mémoire d'un processus.
- **Mémoire virtuelle** : dispositif par lequel un processus s'exécute
dans un espace d'adressage virtuel qui n'est pas directement celui de la 
mémoire réelle (les barrettes mémoire).
- **MMU (memory management unit)**, circuit chargé de la *génération
d'adresses* d'**adresses logiques** et d'une **table des pages**.
Détecte les **défauts de page** et la violation des permissions
d'accès.
- **Pagination** (système à) : système à mémoire paginée dans lequel
  les pages d'un processus ne sont pas toutes présentes en mémoire
  primaire, mais peuvent être stockées en mémoire secondaire
  (**swap**).
- **Swap** : espace réservé sur disque pour servir de **mémoire
  secondaire**
- **Thrashing**, voir *Écroulement du système*
- **Working set**, voir *Ensemble de travail*





[^8]: Un comparateur est un soustracteur, dont on utilise le signe du résultat.

[^9]: par exemple parce qu'ils font de l'**allocation dynamique**
    (instruction `new` en C++, Java, etc).

[^11]: pour éviter les confusions, on parle de  "page" pour les adresses logiques, et de  "cadre" pour les adresses physiques.


[^13]: Une ressource plus abondante, moins chère, mais aussi d'accès plus lent
    que la mémoire centrale (on ne peut pas tout avoir).

[^14]: dans le sens de "faire défaut", c'est-a-dire *manquer*.

