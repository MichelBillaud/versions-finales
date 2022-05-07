#include <stdbool.h>
#include <stdint.h>

#define TAILLE_MEMOIRE (1<<12)
union Mot {
  int16_t  s;
  uint16_t u;
};

enum Operation {
  HALT,
  LOAD,	STORE,
  LOADX, STOREX,
  ADD,	SUB,
  JMP,	JNEG,
};

union Mot nInstruction(unsigned int op, unsigned int adr);
union Mot nEntier(int e );
void      voir_donnees (union Mot memoire[], int debut, int fin);
void      voir_code (union Mot memoire[], int debut, int fin);
void      simulation (union Mot memoire[]);
