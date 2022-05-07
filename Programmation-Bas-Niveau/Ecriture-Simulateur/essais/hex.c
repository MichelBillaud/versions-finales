/*
 * lecture (sur entrée standard) et écriture d'un nombre en hexadécimal
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
     unsigned int n;
     do {
          printf("hexa ? ");
          scanf("%x", & n);
          printf("decimal = %d, hexadecimal = %x\n", n, n );
     } while (n!=0);
     return EXIT_SUCCESS;
}

