


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	for(int i=0; i<5; i++) {
		printf("%p\n", malloc(1));
	}
	return 0;
}

