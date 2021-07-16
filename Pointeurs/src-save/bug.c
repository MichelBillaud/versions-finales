

#include <stdio.h>

int main()
{
	
int nombre = 0;
int *pointeur = nombre;
*pointeur = 1234;
printf("%d\n", *pointeur);
	return 0;
}

