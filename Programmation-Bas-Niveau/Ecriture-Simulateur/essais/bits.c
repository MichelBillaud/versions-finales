/*
 * décomposition de mots
 * lus sur l'entrée standard
 */

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
     uint16_t mot;
     while (scanf("%" SCNx16, & mot) == 1) {
          unsigned int code     =  (mot >> 12);      /* décalage 12 bits à droite */
          unsigned int operande =  (mot & 0xfff);    /* masquage */
          printf("mot = %04x, code = %x, operande = %x\n",
                 mot, code, operande);
     }
     return EXIT_SUCCESS;
}

