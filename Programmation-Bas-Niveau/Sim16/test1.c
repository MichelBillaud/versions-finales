#include <stdlib.h>

#include "sim16.h"

int main (void)
{
  union Mot memoire[TAILLE_MEMOIRE];


  memoire[0] = nInstruction(LOAD,   10);
  memoire[1] = nInstruction(ADD,    11);
  memoire[2] = nInstruction(SUB,    12);
  memoire[3] = nInstruction(STORE,  13);
  memoire[4] = nInstruction(HALT,   0);

  memoire[10] = nEntier(30);
  memoire[11] = nEntier(13);
  memoire[12] = nEntier(1);
  memoire[13] = nEntier(0);

  voir_code (memoire, 0,4);

  simulation (memoire);
  voir_donnees (memoire,10,13);
  return EXIT_SUCCESS;
}
