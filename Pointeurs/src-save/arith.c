

#include <stdio.h>


int main()
{
	double un_double = 1234.56;
	
	printf("adresse de un_double = %p\n\n", & un_double);
	
	double * p = & un_double;
	
	for(int k = 0; k < 4; k++) {
		printf("       valeur de p+%d = %p\n", k, p+k);
	}
	return 0;
}

