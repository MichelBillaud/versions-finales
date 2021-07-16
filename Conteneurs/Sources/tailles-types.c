/**
 * Affichage des tailles de divers types de base.
 * 
 * Les tailles dépendent du compilateur, 
 * sauf pour pour char (toujours 1).
 */
#include <stdio.h>

int main()
{
    printf("type\ttaille\n----\t------\n");
    printf("char\t%zu\n",   sizeof(char)); 
    printf("int\t%zu\n",    sizeof(int));
    printf("long\t%zu\n",   sizeof(long));
    printf("float\t%zu\n",  sizeof(float));
    printf("double\t%zu\n", sizeof(double));
    return 0;
}

