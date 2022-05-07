/*
 * 	simulateur pour un processeur simple
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "sim16.h"



char * mnemonique[16] = {
  "halt",
  "load",  "store",
  "loadx", "storex",
  "add", "sub",
  "jmp", "jneg",
  // codes opérations illégaux - pour l'instant
  "op9?", "op10?", "op11?",
  "op12?", "op13?", "op14?", "op15?"
};


union Mot nInstruction(unsigned int op, unsigned int adr) {
  union Mot m;
  m.u =  (op << 12) | (adr & 0xFFF) ;
  return m;
}

union Mot nEntier(int e ) {
  union Mot m;
  m.s = e;
  return m;
}

void voir_donnees (union Mot memoire[], int debut, int fin)
{
  int nb = 0; // déjà écrits sur la ligne
  printf("--- vue donnes en memoire, adresses %d a %d\n", debut,fin);
  for (int i = debut; i <=fin; i++, nb++) {
    if (nb == 8) {
      printf("\n");
      nb = 0;
    }
    printf("%04d:%4d  ",i,memoire[i].s);
  }
  printf("\n");
}

void voir_code (union Mot memoire[], int debut, int fin)
{
  int nb = 0; // déjà écrits sur la ligne
  printf("--- vue code en memoire, adresses %d a %d\n", debut,fin);
  for (int i = debut; i <=fin; i++, nb++) {
    union Mot instr      = memoire[i];
    unsigned int op  = (instr.u >> 12) & 0xF;
    unsigned int adr = instr.u & 0xFFF;
    printf("%04d : %-5s %d\n", i, mnemonique[op], adr);
  }
}


void simulation (union Mot memoire[])
{
  bool tourne = true,
    trace = true;

  printf("-- debut simulation\n");
  unsigned short int cp = 0;  // compteur de programme
  union Mot  a  = { .u = 0};         // accumulateur
  union Mot  ri;            // registre d'instruction
  while (tourne) {
    // chargement instruction,
    ri = memoire[cp]; // reg.instruction
    unsigned int op  = (ri.u >> 12) & 0xF;
    unsigned int adr = ri.u & 0xFFF;
    if (trace) {
      printf("trace> execution instruction %d : %4s %d\n",
             adr,  mnemonique[op], adr);
    };
    cp ++;
    switch (op) {
    case HALT :
      tourne = false;
      break;
    case LOAD :
      // printf("*** chargement adresse %d\n",adr);
      a = memoire[adr];
      break;
    case STORE:
      memoire[adr] = a;
      break;
    case ADD :
      a.s += memoire[adr].s;
      break;
    case SUB :
      a.s -= memoire[adr].s;
      break;
    case JMP :
      cp = adr;
      break;
    case JNEG :
      if (a.s < 0) cp = adr;
      break;
    }
    if (trace) {
      printf("trace> cp=%d, a=%d (0x%04x)\n",
             cp, a.s, a.u);
    }
  }
  printf("--- fin simulation\n");
}
