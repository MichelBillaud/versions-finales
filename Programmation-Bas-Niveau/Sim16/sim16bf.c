/*
 * 	simulateur pour un processeur simple
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAILLE_MEMOIRE 4094

enum Operation {
  HALT,
  LOAD,	STORE,	ADD,	SUB,
  JMP,	JNEG
};

char * mnemonique[16] = {
  "halt",
  "load",  "store", "add", "sub",
  "jmp", "jneg",
  // codes opérations illégaux - pour l'instant
  "op7?",
  "op8?", "op9?", "op10?", "op11?",
  "op12?", "op13?", "op14?", "op15?"
};


struct Instruction {
  unsigned short op : 4;
  unsigned short adr : 12;
};

union Mot {
  struct Instruction i;
  short int d;
};

union Mot nInstruction(int op, int adr) {
  union Mot m;
  m.i.op = op;
  m.i.adr = adr;
  return m;
}

union Mot nEntier(int e ) {
  union Mot m;
  m.d = e;
  return m;
}

void voir_memoire(union Mot memoire[], int debut, int fin)
{
  int nb = 0; // déjà écrits sur la ligne
  printf("--- vue memoire, adresses %d a %d\n", debut,fin);
  for (int i = debut; i <=fin; i++, nb++) {
    if (nb == 8) {
      printf("\n");
      nb = 0;
    }
    printf("%04d:%4d  ",i,memoire[i].d);
  }
  printf("\n");
}


void simulation(union Mot memoire[])
{
  printf("taille = %ld\n", sizeof(union Mot));

  bool tourne = true,
       trace = true,
       pasapas = true;
  printf("-- debut simulation\n");
  unsigned short int cp = 0;  // compteur de programme
  short          int a  = 0;  // accumulateur
  struct         Instruction ri; // registre d'instruction
  while (tourne) {
    // chargement instruction,
    ri = memoire[cp].i; // reg.instruction
    if (trace) {
      printf("trace> execution instruction %d : %4s %d\n",
             ri.op, mnemonique[ri.op], ri.adr);
    };
    cp ++;
    switch (ri.op) {
    case HALT :
      tourne = false;
      break;
    case LOAD :
      a = memoire[ri.adr].d;
      break;
    case STORE:
      memoire[ri.adr].d = a;
      break;
    case ADD :
      a += memoire[ri.adr].d;
      break;
    case SUB :
      a -= memoire[ri.adr].d;
      break;
    case JMP :
      cp = memoire[ri.adr].d;
      break;
    case JNEG :
      if (a < 0) cp = memoire[ri.adr].d;
      break;
    }
    if (trace) {
      printf("trace> cp=%d, a=%d (0x%04x)\n",
             cp, a, a);
    }
  }
  printf("--- fin simulation\n");
}

int main()
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

  simulation(memoire);
  voir_memoire(memoire,10,13);
  return EXIT_SUCCESS;
}
