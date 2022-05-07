#
# Tri d'un tableau  T[N] par sélection
#
#
#	pour i de 0 à n-1
#		imin = i
#	        min = t[i]
#		pour j = i+1 à n-1
#	            si t[j] <= min
#	               imin = j
#	               min  = t[j]
#	        echanger t[i] t[imin]

	loadi 	0
	store	i
bcle_i
	load   	i	# si i == n  fin boucle sur i
	sub    	n
	jzero  	fin_i

	load	i	# imin = i
	store	imin

	loadi	t	# min = t[i]
	add	i
	store	ptr
	loadx 	ptr
	store 	min

	loadi 	1	# j = i+1
	add	i
	store	j
bcle_j
	load	j
	sub	n
	jzero	fin_j

	loadi	t	# tj = t[j]
	add	j
	store	ptr
	loadx	ptr
	store	tj
	
	load	min     # si tj > min  avancer j
	sub	tj
	jneg	incr_j

	load	j	# imin = j
	store	imin

	load 	tj	# min = tj
	store 	min
incr_j
	loadi	1	# j++
	add	j
	store	j
	jmp	bcle_j
fin_j
	# echange
	loadi 	t	# ti = t[i]
	add	i
	store	ptr
	loadx	ptr
	store	ti
	load	min	# t[i] = min
	storex	ptr

	loadi 	t	# t[imin] = ti
	add	imin
	store	ptr
	load 	ti
	storex	ptr
		
incr_i
	loadi  	1	# i++
	add    	i
	store  	i
	jmp 	bcle_i
fin_i
	halt	0

# ------------------------------
	
i	word	0
j 	word	0
min	word    0
imin	word    0
ti	word	0
tj	word	0	
ptr	word 	0

# ------------------------------
n 	word	10
	
t	word	1111
	word	4444
	word	2222
	word	8888
	word	5555
	
	word	7777
	word	0
	word	9999
	word	6666
	word	3333
# -------------------------------
	