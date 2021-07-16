
#include <stdio.h>

int main(int argc, char **argv)
{
	printf("quel est votre age ?\n");
	int age;
	int *adresse_age  = & age;
	
	scanf("%d", adresse_age);
	int annee = 2017-age;
	printf("vous etes né en %d\n", annee);
	
	printf("adresse de age =  %p", adresse_age);
	
	return 0;
}
