#
# Calcul de fibonacci
# r�cursif
#

# algo
#  fib(n):
#    si n < 2
#	retourner n
#    a = fib(n-1)
#    b = fib(n-2)
#    retourner a+b

# conventions d'appel
#
#  En entr�e : Acc contient n
#              cadre   contient l'adresse d'un espace en sommet de pile
#                      disponible pour l'instance de la fonction
#  En sortie : Acc contient n


main
	loadi	pile
	store   cadre
	
	load    N   # calcul fib(N)
	call	fib
	store   R
	halt	0

N	word  	8
R	word 	0
# -------------------------------------


fib	word	0      # adresse de retour

	store  tmp    # copie de N
	loadi   1      # si N>1, aller � cas_general
	sub	tmp
	jneg	cas_general
	load	tmp 	# sinon retourner N
	jmpx	fib
	
cas_general
	load	tmp
	storex 	cadre  # sauvegarde N dans cadre[0]

	loadi 	1      # sauvegarde adresse de retour
	add	cadre  # dans cadre[1]
	store 	ptr
	load	fib
	storex	ptr
				# contenu du cadre de pile :
				#    cadre[0] = n
				#    cadre[1] = adresse de retour
	
	loadi	2	# allocation nouveau cadre
	add	cadre
	store 	cadre
	loadi	-1	# appel fib(n-1)
	add	tmp
	call	fib
	store 	res	# copie r�sultat
	loadi	-2	# lib�ration cadre		
	add	cadre
	store 	cadre

	loadi	2 	# sauvegarde r�sultat fib(n-1) dans cadre[2]
	add	cadre
	store	ptr
	load	res
	storex	ptr

	loadx	cadre   # recup�ration de N dans tmp
	store	tmp	
				# contenu du cadre de pile :
				#    cadre[0] = n
				#    cadre[1] = adresse de retour
				#    cadre[2] = valeur de fib(n-1)
	
	loadi	3	# allocation nouveau cadre
	add	cadre
	store 	cadre
	loadi	-2	# appel fib(n-2)
	add	tmp
	
	call	fib
	store 	res	# copie r�sultat fib(n-2)
	loadi	-3	# lib�ration cadre
	
	add	cadre
	store 	cadre	                
	loadi	1       # r�cup�ration de l'adresse de retour
	add	cadre
	store	ptr
	loadx	ptr
	store	fib
	
	loadi	2       # calcul fib(n-1) + fib(n-2) 
	add	cadre
	store	ptr
	loadx	ptr
	add	res

	jmpx fib

# -----------------------------------
ptr	word	0
tmp	word	0
res	word	0
# ------------------------------------
cadre	word   0       # pointeur de cadre de pile
pile    word   0       # la pile commence ici
	               # ...
