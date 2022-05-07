# Programme pour calcul de la valeur absolue
# version non optimisée

      load  X       # si X<0 aller à OPPOSE
      jneg OPPOSE

      load  X       # R = X
      store R

      jmp   SUITE   # aller à SUITE
OPPOSE
      loadi 0        # R = 0-X
      sub  X
      store R
SUITE
      halt 0
# 
# données
#
X     word  -3
R     word  0
