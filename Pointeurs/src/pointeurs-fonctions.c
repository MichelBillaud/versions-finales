

#include <stdio.h>

void afficher(int n) {
	printf("%d\n", n);
}

void foo()
{
	int a[10], b[10];
	// a = b;
}
int main()
{
	int tableau[] = { 111, 22, 3333};
	
	void (*adr_fonction)(int);
	adr_fonction =  afficher;
	for (int i=0; i<3; i++) {
		adr_fonction(tableau[i]);
	}
	return 0;
}

