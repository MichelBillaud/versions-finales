/**
 * Affichage d'adresses de variables.
 * 
 */
#include <stdio.h>

int glob1 = 12;
float glob2 = 34;

int main()
{
    int loc1 = 33;
    float loc2 = 3.14;
    printf("var.\tadresse\n----\t------\n");
    printf("glob1\t%p\n",  (void *)  & glob1); 
    printf("glob2\t%p\n",  (void *)  & glob2);
    printf("loc1\t%p\n",   (void *)  & loc1);
    printf("loc2\t%p\n",   (void *)  & loc2);
    return 0;
}

