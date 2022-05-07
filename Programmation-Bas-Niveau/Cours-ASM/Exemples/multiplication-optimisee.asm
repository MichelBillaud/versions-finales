#
# Multiplication 
#
# optimisée

# p = 0
# pour I de 0 à B-1
#   P += B

  loadi 0   #  P = I = 0
  store P

boucle      # si B==I aller à fin
  store I
  sub  B 
  jzero fin

  load A    # P += A
  add P
  store P

  loadi 1   # I += 1
  add  I
  jmp boucle  # aller à boucle 

fin
  halt 0


A word 7
B word  6
P word  0
I word 0