#include <stdlib.h>
#include "sim16.h"

int main()
{
  union Mot memoire[TAILLE_MEMOIRE];

  memoire[0] = nInstruction( LOAD, 10);  // n
  memoire[1] = nInstruction( JNEG, 8);
  memoire[2] = nInstruction( ADD, 11);   // +somme
  memoire[3] = nInstruction( STORE, 11); // -> somme
  memoire[4] = nInstruction( LOAD, 10);  // n
  memoire[5] = nInstruction( SUB, 12);   // -1
  memoire[6] = nInstruction( STORE, 10); // -> n
  memoire[7] = nInstruction( JMP, 1);
  memoire[8] = nInstruction( HALT, 0);

  memoire[10] = nEntier( 5);  // n
  memoire[11] = nEntier( 0);  // somme
  memoire[12] = nEntier( 1);  // =1

  voir_code (memoire, 0,8);
  voir_donnees (memoire,10,12);

  simulation (memoire);
  voir_donnees (memoire,10,12);
  return EXIT_SUCCESS;
}
