#
# Calcul de la somme des entiers de 1 � N
#
    loadi 0    # S=0
    store S

    loadi 1    # K=1
    store K

BOUCLE         # si K>N aller � suite
    load  N    # - calcul N-K
    sub   K
    jneg  SUITE   
    
    load  S    # S = S+K 
    add   K 
    store S

    loadi  1   # K = K+1
    add    K
    store  K
    jmp   BOUCLE

SUITE
    halt 0
#
# variables
#
N   word  5
K   word  0
S   word  0
	