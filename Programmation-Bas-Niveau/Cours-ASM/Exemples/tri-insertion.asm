#
# tri par insertion
#

# pour i de 0 à n-1
#   j = i-1
#   tant que j >= 0
#        et t[j] < t[j+1]
#      echanger t[j], t[j+1]
#   j--

     loadi 0
     store i
loop_i
     sub n
     jzero end_i

     loadi -1
     add   i
     store j
loop_j
     jneg  end_j
     loadi t
     add   j
     store ptj
     loadx ptj
     store tj

     loadi 1
     add   ptj
     store ptjp1
     loadx ptjp1
     sub tj
     jneg end_j

     loadx ptjp1
     storex ptj
     load tj
     storex ptjp1
next_j
     loadi -1
     add    j
     store  j
     jmp loop_j
end_j
next_i
     loadi 1
     add   i
     store i
     jmp   loop_i
end_i
     halt 0

#
# variables
#
i word 0
j word 0

tj    word 0  # valeur dep t[j]
ptj   word 0  # pointeur vers t[j]
ptjp1 word 0  # pointeur vers t[j+1]

#
# tableau
#
n      word 10
t      word 1
       word 4
       word 2
       word 8
       word 5
       word 7
       word 0
       word 3
       word 6
       word 9