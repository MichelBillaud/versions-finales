#
#  Somme des �l�ments d'un tableau
#
#  donn�es  : N, T[N]
#  r�sultat : S
	
	loadi  	0	# S = 0
	store	S
	store	K       # K = 0

	# pour K de 0 � N-1

Boucle
	load 	N    	# si K==N aller � Fin
	sub 	K
	jzero	Fin

	loadi 	T	# P = & T[K]
	add	K
	store	P

	loadx	P       #  S += *P
	add	S
	store	S

	loadi	1	# K++
	add	K
	store	K

	jmp	Boucle
	
Fin
	halt	0
#
# tableau de 5 cases
#
N  	word 	5	
T 	word  	10000
	word  	2000
	word   	300
	word    40
	word	5
#
# variables
#
K 	word 	0   	# indice
P       word 	0     	# pointeur
S	word 	0     	# somme