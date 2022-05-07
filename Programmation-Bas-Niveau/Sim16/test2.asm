	LOAD n
boucle	JNEG fin




	ADD somme
	STORE somme
	LOAD n
	SUB c1
	STORE n
	JMP boucle
fin	HALT 0
n 	word 5
somme 	word 0
c1	word 1
