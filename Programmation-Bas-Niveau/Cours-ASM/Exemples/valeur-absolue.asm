# Programme pour calcul de la valeur absolue
# version non optimis�e

      load  X       # si X<0 aller � OPPOSE
      jneg OPPOSE

      load  X       # R = X
      store R

      jmp   SUITE   # aller � SUITE
OPPOSE
      loadi 0        # R = 0-X
      sub  X
      store R
SUITE
      halt 0
# 
# donn�es
#
X     word  -3
R     word  0
