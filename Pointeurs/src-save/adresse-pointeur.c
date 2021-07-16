

#include <stdio.h>

int main()
{
	int nombre = 1234;
	int *adr_nombre = & nombre;   // adr_nombre est un pointeur
	
	printf("le nombre vaut %d\n",         nombre);
	printf("il est à l'adresse   %p\n", & nombre);
	printf("le pointeur contient %p\n",   adr_nombre);
	printf("il est à l'adresse   %p\n", & adr_nombre);
	
	return 0;
}

