/*
 * 	simulateur pour un processeur simple
 */

// Pour emacs :
// Local Variables:                                                   
// compile-command: "LANG=C make sim16"
// End:                                                          

#define UNUSED(x) (void)(x)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>


#define TAILLE_MEMOIRE_MIN      1
#define TAILLE_MEMOIRE_DEFAUT 128
#define TAILLE_MEMOIRE_MAX   2048
 
union  Mot16 {
  int16_t  s;
  uint16_t u;
};

enum Operation {
  LOADI,
  LOAD,	
  LOADX, 
  STORE,
  STOREX,
  ADD,	
  SUB,
  JMP,	
  JNEG,
  JZERO,
  JMPX, 
  CALL,
  HALT,

  ILLEGAL13,
  ILLEGAL14,
  ILLEGAL15
};

char * mnemonique[] = {
  [LOADI]  = "loadi",
  [LOAD]   = "load",
  [LOADX]  = "loadx",
  [STORE]  = "store",
  [STOREX] = "storex",
  [ADD]    = "add",	
  [SUB]    = "sub",
  [JMP]    = "jmp",	
  [JNEG]   = "jneg",
  [JZERO]  = "jzero",
  [JMPX]   = "jmpx", 
  [CALL]   = "call",
  [HALT]   = "halt",

  [ILLEGAL13] = "illegal13",
  [ILLEGAL14] = "illegal14",
  [ILLEGAL15] = "illegal15",
};


union Mot16 nInstruction(unsigned int op, unsigned int adr) {
  union Mot16 m;
  m.u =  (op << 12) | (adr & 0xFFF) ;
  return m;
}

union Mot16 nEntier(int e ) {
  union Mot16 m;
  m.s = e;
  return m;
}

// état de la machine

typedef enum {
  S_OK,
  S_HALTED,
  S_ERROR_OP,
  S_ERROR_MEM,
} Etat;

char *etats[] = {
  "ok",
  "halted",
  "opcode error",
  "address error",
};

struct Machine {
  size_t             memsize;
  union Mot16        *mem;
  uint16_t           cp;    // compteur de programme
  union Mot16        a ;    // accumulateur
  Etat               status;
};

// paramètres du simulateur

enum Mode {
  M_INTERACTIF,
  M_TRACE,
  M_SILENCIEUX
};

struct Simulation {
  enum Mode mode;
  bool      tourne;
  int       nbMots;  // nombre de mots chargés en mémoire
};


void voir_donnees (struct Machine *m, int debut, int fin)
{
  int nb = 0; // déjà écrits sur la ligne
  printf("--- vue données en memoire, adresses %d a %d\n", debut,fin);
  for (int i = debut; i <=fin; i++, nb++) {
    if (nb == 8) {
      printf("\n");
      nb = 0;
    }
    printf("%04d:%4d  ",i,m->mem[i].s);
  }
  printf("\n");
}

void voir_memoire (struct Machine * m, int debut, int fin)
{
  int nb = 0; // déjà écrits sur la ligne
  printf("--- Contenu de la memoire, adresses %d a %d\n", debut,fin);
  printf(" addr\thexa\tdecimal\tinstr adr (dec)\n"
	 " ----\t----\t-------\t----------------\n");
  for (int i = debut; i <=fin; i++, nb++) {
    union Mot16 mot      = m->mem[i];
    unsigned int op  = (mot.u >> 12) & 0xF;
    unsigned int adr = mot.u & 0xFFF;
    printf("%c%4d\t%04X\t%6d\t%-5s %d\n",
	   i == m->cp ? '*' : ' ',
	   i, 
	   mot.u,  mot.s,
	   mnemonique[op], adr);
  }
}

void voir_registres(struct Machine * m) 
{    
  union Mot16 instr      = m->mem[m->cp];
    unsigned int op  = (instr.u >> 12) & 0xF;
    unsigned int adr = instr.u & 0xFFF;
    printf("* Status=%s, A=%d (0x%04X), "
	   "CP=%d -> [%s %d]\n",
	   etats[m->status],
	   m->a.s, m->a.u, 
	   m-> cp, mnemonique[op], adr); 
}

void executer_instruction(struct Machine *m, struct Simulation *s)
{
  UNUSED(s);
  uint16_t ri = m->mem[m->cp].u; // reg.instruction
  unsigned int op  = (ri >> 12) & 0xF;
  unsigned int adr = ri & 0xFFF;
  unsigned int eadr;

  m->cp ++;
  switch (op) {
  case HALT :
    m->status   = S_HALTED;
    m-> cp--;
    break;
  case LOAD :
    m->a        = m->mem[adr];
    break;
  case STORE:
    m->mem[adr] = m->a;
    break;
  case ADD :
    m->a.s      += m->mem[adr].s;
    break;
  case SUB :
    m->a.s      -= m->mem[adr].s;
    break;
  case JMP :
    m->cp       = adr;
    break;
  case JMPX :
    eadr = m->mem[adr].u;
    if (eadr >= m->memsize) 
      m->status = S_ERROR_MEM;
    else {
      // printf("saut indirect %d -> %d\n", adr, eadr); 
      m->cp  = eadr;
    }
    break;
  case CALL :
    // printf("saut indirect %d -> %d\n", m->cp, adr+1); 
    m->mem[adr].u = m->cp;
    m->cp         = adr+1;
    break;
  case JNEG :
    if (m->a.s < 0) 
      m->cp = adr;
    break;
  case JZERO :
    if (m->a.s == 0) 
      m->cp = adr;
    break;
  case LOADX :
    eadr = m->mem[adr].u;
    if (eadr >= m->memsize) 
      m->status = S_ERROR_MEM;
    else
      m->a  = m->mem[eadr];
    break;
  case STOREX:
    eadr = m->mem[adr].u;
    if (eadr >= m->memsize) 
      m->status = S_ERROR_MEM;
    else
      m->mem[eadr] = m->a;
    break;
  case LOADI:
    // avec extension de signe de la donnée sur 12 bits
    m->a.s = (int16_t)(adr << 4) >> 4; 
    break;
  default:
    m->status = S_ERROR_OP;
    break;

  }
}

void simulation (struct Machine * m, struct Simulation s)
{     
  if (s.mode != M_SILENCIEUX) {
    printf("-- debut simulation\n");
    voir_memoire(m, 0, s.nbMots-1);
  }
  m->status = S_OK;
  m->cp      = 0;    
  m->a.u     = 0;

  s. tourne = true;

  while (s.tourne) {
    if (s.mode != M_SILENCIEUX) {
      voir_registres(m);
    };

    if (s.mode == M_INTERACTIF) {
      char cmd[10];
      printf("commande [vsq] ");
      scanf("%8s", cmd);
      // l'exécuter
      if (strcmp(cmd,"v") == 0) {
	voir_memoire(m, 0, s.nbMots-1);
      } else if (strcmp(cmd,"s") == 0) {
	executer_instruction(m, &s);
      } else if (strcmp(cmd,"q") == 0) {
	s.tourne = false;
      } else {
	printf("votre commande  %s est inconnue\n", cmd);
      } 
    }
    else {
      executer_instruction(m, &s);
      if (m->status != S_OK) {
	s.tourne = false;
      }
    }
  }
  printf("--- fin simulation\n");
  voir_memoire(m, 0, s.nbMots-1);
  voir_registres(m);
}

// retourne le nombre de mots chargés, -1 si erreur
int chargerExecutable(struct Machine *m, char chemin[])
{
  FILE * f = fopen(chemin, "r");
  if (! f) {
    return -1;
  }
  unsigned taille = 0; 
  unsigned int n;
  while (fscanf(f,"%x", &n)==1) {
    m->mem[taille++].u = n;
    if ( taille > m->memsize) {
      fprintf(stderr, "Taille memoire %zu insuffisante pour charger le programme\n",
	      m->memsize);
      return -1;
    }
  }
  fclose(f);
  return taille;
}

void afficheUsage(char prog[])
{
  printf("Usage : %s [-stih] fichier.hex\n"
	"Charge le fichier.hex dans la mémoire du simulateur\n"
	"et lance l'exécution\n"
	"Options:\n"
	"  -i         simulation interactive (defaut)\n"
	"  -t         simulation avec trace\n"
	"  -s         simulation silencieuse\n"
	"  -m taille  taille memoire [1-2048], defaut = 128\n"
	"  -h  help\n"
	, prog);
}

int main(int argc, char * argv[])
{
  struct Simulation s = { .mode = M_INTERACTIF };
  struct Machine    m = { .memsize = 128 };

  opterr = 0;
  int c;
  bool voirAide = false;

  while ((c = getopt (argc, argv, "stihm:")) != -1)
    switch (c) {
    case 's':
      s.mode = M_SILENCIEUX;
      break;
    case 't':
      s.mode = M_TRACE;
      break;
    case 'i':
      s.mode = M_INTERACTIF;
      break;
    case 'm':
      m.memsize = atoi(optarg);
      break;
    case 'h':
      voirAide = true;
      break;
    case '?':
      if (isprint (optopt))
	fprintf (stderr, "Option inconnue `-%c'.\n", optopt);
      else
	fprintf (stderr,
		 "Option inconnue `\\x%x'.\n",
		 optopt);
      afficheUsage(argv[0]);
      return EXIT_FAILURE;
    default:
      abort ();
    }
  
   if (voirAide) {
     afficheUsage(argv[0]);
     return EXIT_SUCCESS;
   }

   if (optind != argc-1) {
     fprintf(stderr, "manque nom du fichier\n");
     return EXIT_FAILURE;
   } 

   if (m.memsize < TAILLE_MEMOIRE_MIN || m.memsize > TAILLE_MEMOIRE_MAX) {
     fprintf(stderr, "La taille memoire doit etre entre %d et %d\n",
	     TAILLE_MEMOIRE_MIN, TAILLE_MEMOIRE_MAX);
     return EXIT_FAILURE;
   }
   m.mem = (union Mot16 *) malloc(m.memsize * sizeof(union Mot16));
   
   s.nbMots = chargerExecutable(&m, argv[optind]);
   if (s.nbMots < 0) {
     perror("lecture exécutable");
     return EXIT_FAILURE;
   }
   printf("%d mots lus\n", s.nbMots);
   
   voir_memoire(&m, 0, s.nbMots-1);
   simulation (&m, s);
   free(m.mem);

  return EXIT_SUCCESS;
}
