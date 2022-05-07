#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <inttypes.h>
#include <stdbool.h>
#include <ctype.h>
#include <search.h>
#include <unistd.h>

#define MAX_PATH_LEN 1024

// macro pour éviter les avertissements sur les paramètres 
// sciemment inutilisés
#define UNUSED(x) (void)(x)

#define ERR_OPT_INCONNUE        "Erreur 101 : Option inconnue `-%c'.\n"
#define ERR_OPT_CAR_INCONNU     "Erreur 102 : Option inconnue `\\x%x'.\n"
#define ERR_SUFFIXE_ASM_ATTENDU "Erreur 103 : Le nom du source doit se termine par .asm\n"
#define ERR_OUVERTURE_LECTURE   "Erreur 201 : ne peut pas ouvrir '%s' en lecture\n"
#define ERR_OUVERTURE_ECRITURE  "Erreur 202 : ne peut pas ouvrir '%s' en écriture\n"
#define ERR_CODOP_INCONNU       "Erreur 301 ligne %d : code operation '%s' inconnu\n"
#define ERR_ARGUMENT_MANQUANT   "Erreur 302 ligne %d : argument attendu pour '%s'\n"
#define ERR_DOUBLE_DEFINITION   "Erreur 303 ligne %d : symbole '%s' deja defini ligne %d\n"
#define ERR_SYMBOLE_INDEFINI    "Erreur 401 : symbole '%s' non defini (lignes" 
#define ERR_SYMBOLE_INDEFINI_L "%d "
#define ERR_SYMBOLE_INDEFINI_NL ")\n"

#define ERR_ERREURS "\n%d erreur(s).\n"
#define ERR_ABANDON "%d erreur(s). Abandon.\n"

// ------------------------------------------------------------

typedef uint16_t Mot16;

struct Reference {
  int ligne;
  int position;
  Mot16 masque;
};

struct Symbole {
  char             * nom;
  int                ligne;
  Mot16              valeur;
  struct Reference * tRef;   // tableau extensible de références
  int maxRef, nbRef ;        // taille et nombre de cases occupées 
};


struct TypeInstruction {
    char    *op;
    Mot16   codeOperation;
    Mot16   masque;
};

// ----------------------------------------------------------
// Variables globales
// ----------------------------------------------------------


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

#define TI(nom,code)  { nom, code << 12, 0xFFF }

struct TypeInstruction typesInstructions[] =
   {
     TI("loadi",  LOADI),
     TI("load",   LOAD),
     TI("loadx",  LOADX),
     TI("store",  STORE),
     TI("storex", STOREX),
     TI("add",    ADD),
     TI("sub",    SUB),
     TI("jmp",    JMP),
     TI("jneg",   JNEG),
     TI("jzero",  JZERO),
     TI("jmpx",   JMPX),
     TI("call",   CALL),
     TI("halt",   HALT),
   };

const int nbtypesInstructions = sizeof(typesInstructions) 
  / sizeof(struct TypeInstruction);


FILE * src;
FILE * hex;
FILE * lst;

void * tableDesSymboles = NULL;
int    nbErreurs = 0;
char * caracteresDansSymbole =  "_$";

Mot16    mots[1024];
int      nbMots = 0;

// ------------------------------------------------------------


int comparerTypeInstruction (const void *p1, const void *p2)
{
  struct TypeInstruction 
    *d1 = (struct TypeInstruction *) p1,
    *d2 = (struct TypeInstruction *) p2;
  return strcasecmp(d1->op, d2->op);
}

// ------------------------------------------------------------

void trierTypesInstructions()
{
  qsort(typesInstructions, nbtypesInstructions, 
	sizeof(struct TypeInstruction), comparerTypeInstruction);
}

// ------------------------------------------------------------

struct TypeInstruction * typeInstruction(char op[])
{
  struct TypeInstruction query = {op, 0, 0};
  return bsearch(&query, typesInstructions, nbtypesInstructions, 
		 sizeof(struct TypeInstruction), 
		 comparerTypeInstruction);
}

// ------------------------------------------------------------
//   Table des symboles
/*
   A chaque symbole (chaine) est associé
   - le numéro de la ligne où il est défini (-1: indéfini, 0: prédéfini) 
   - sa valeur (si défini)
   - la liste des endroits où il est employé (references)
	 - numéro de ligne
	 - la rustine (patch) à appliquer au code généré
	      - position dans le code
	      - masque 

    Par exemple position=42 et masque=0x0FF signifie que la valeur du symbole
    devra être mise dans l'octet de poids faible du mot de position 42.
 */

 void initialiserTableDesSymboles()
 {
   tableDesSymboles = NULL;
 }

// ------------------------------------------------------------

 int comparerSymbole(const void *a, const void *  b)
 {
   struct Symbole 
     * pa = (struct Symbole *) a,
     * pb = (struct Symbole *) b;
   return strcmp(pa->nom, pb->nom);
 }

// ------------------------------------------------------------

struct Symbole *  creerSymbole(char nom[]) 
 {
   struct Symbole *s = malloc(sizeof(struct Symbole));
   s -> nom = strndup(nom,strlen(nom)+1);
   s -> ligne  = -1;
   s -> valeur = 0;
   s -> nbRef  = 0;
   s -> maxRef = 0;
   s -> tRef   = NULL;
   tsearch(s,&tableDesSymboles, comparerSymbole); 
   return s;
 }

// ------------------------------------------------------------

struct Symbole * chercherSymbole(char nom[])
 {
   struct Symbole requete = { nom, 0, 0,  NULL, 0, 0};
   void *r = tfind ( & requete, &tableDesSymboles, comparerSymbole);
   return (r ==NULL) ? creerSymbole(nom) : *(struct Symbole **) r;
 }

// ------------------------------------------------------------

 bool symboleEstDefini(char * nom) {
   struct Symbole *s = chercherSymbole(nom);
   return s->ligne >= 0;
 }

// ------------------------------------------------------------

 void definirSymbole(char nom[], int ligne, int valeur)
 {
   struct Symbole *s = chercherSymbole(nom);
   s -> ligne = ligne;
   s -> valeur = valeur;
 }

// ------------------------------------------------------------

 void ajouterReference(char nom[], int ligne, int position, int masque)
 {
   struct Symbole *s = chercherSymbole(nom);

   // au besoin ajouter de la place pour des références supplémentaires
   if (s->nbRef == s->maxRef) {
     s->maxRef = (s->maxRef == 0) ? 8 : 2*s->maxRef;
     s->tRef = realloc(s->tRef, s->maxRef * sizeof(struct Reference));
   }
   struct Reference * r = s->tRef + (s->nbRef++);
   r -> ligne    = ligne;
   r -> position = position;
   r -> masque   = masque;
 }

// ------------------------------------------------------------

void resoudreSymbole (const void  *ptr, 
		     const VISIT  type, 
		     const int    profondeur)
{
  UNUSED(profondeur);
  const struct Symbole *s = *(struct Symbole **)  ptr;
  
  if (type == postorder || type == leaf) {
    if (s->ligne < 0) {
      fprintf(lst,ERR_SYMBOLE_INDEFINI, s->nom);
      fprintf(stderr,ERR_SYMBOLE_INDEFINI, s->nom);
      nbErreurs ++;
      for (int i=0; i < s->nbRef; i++) {
	fprintf(lst,ERR_SYMBOLE_INDEFINI_L, s->tRef[i].ligne);
	fprintf(stderr,ERR_SYMBOLE_INDEFINI_L, s->tRef[i].ligne);
      }
      fprintf(lst,ERR_SYMBOLE_INDEFINI_NL);
      fprintf(stderr,ERR_SYMBOLE_INDEFINI_NL);
    } else {
      // le symbole est défini, on applique les rustines
      for (int i=0; i < s->nbRef; i++) {
	mots[s->tRef[i].position] |= (s-> valeur & s->tRef[i].masque);
      }  
    }
  }
}

// ------------------------------------------------------------

void afficherSymbole (const void  *ptr, 
		     const VISIT  type, 
		     const int    profondeur)
{
  UNUSED(profondeur);
  const struct Symbole *s = *(struct Symbole **)  ptr;
  
  if (type == postorder || type == leaf) {
    fprintf(lst, "%-12s %4d %10d %04X  ",
	    s->nom, s->ligne, s->valeur, s->valeur);
    for (int i=0; i < s->nbRef; i++) {
      fprintf(lst, " %d", s->tRef[i].ligne);
    }
    fprintf(lst, "\n");
  }
}

// ------------------------------------------------------------

bool estNombre(char s[])
{
    int i = (s[0]=='-' ? 1 : 0);
    while (isdigit(s[i])) i++;
    return (s[i] == '\0');
}

// ------------------------------------------------------------

void resoudreReferences()
{
  twalk(tableDesSymboles, resoudreSymbole);
}

// ------------------------------------------------------------

void afficherSymboles() {
  fprintf(lst, "\n"
	  "**********************\n"
	  "* Table des symboles *\n"
	  "**********************\n"
	  "\n");
	  
  fprintf(lst,
	  "Symbole     Ligne   =Decimal =Hex  References\n"
	  "----------  -----   -------- ----  ----------\n");
  twalk(tableDesSymboles, afficherSymbole);
  
  fprintf(lst,"----------  -----   -------- ----  ----------\n\n");

}

// ------------------------------------------------------------

void afficherCode()
{
    if (nbErreurs != 0) {
      fprintf(lst, ERR_ABANDON, nbErreurs);
      fprintf(stderr,ERR_ABANDON, nbErreurs);
      return;
    }
    fprintf(lst, 
	    "*****************\n"
	    "* Image memoire *\n"
	    "*****************\n\n");
    for(int i=0; i<nbMots; i++) {
      fprintf(lst, "%03x:  %04x   (%d)\n", i, mots[i], mots[i]);
    }
}

// ------------------------------------------------------------

void genererFichierHexa()
{
    for (int i=0; i < nbMots; i++) {
      fprintf(hex,"%04x ", mots[i]);
      if (i%8 == 7) 
	fprintf(hex,"\n");
    }
    fprintf(hex,"\n");
}

// ------------------------------------------------------------

void assemblerInstruction(int numero,
                          char label[], 
			  char op[], 
			  char arg[])
{
  /*
  printf("assemblerInstruction(%d,%s,%s,%s)\n",
	 numero, label, op, arg);
  */
  if (strcmp(label, "") != 0) {
    // définir le symbole
    struct Symbole *l = chercherSymbole(label);
    if (l->ligne >= 0) {
      nbErreurs++;
      fprintf(stderr, ERR_DOUBLE_DEFINITION, numero, label, l->ligne);
      fprintf(lst, ERR_DOUBLE_DEFINITION, numero, label, l->ligne);
    } else {
      l->ligne = numero;
      l->valeur = nbMots;
    }
  }
  
  if (strcmp(op,"") == 0)
    return;
  if (strcasecmp(op,"word") == 0) {
    int valeur = 0;
    if (estNombre(arg)) {
      valeur = atoi(arg);
    } else {
      // on suppose que c'est un identificateur
      // dans ce cas : pas de masquage
      ajouterReference(arg,numero,nbMots, ~ 0);
    }
    mots[nbMots++] = valeur;
  } else {
    struct TypeInstruction *p = typeInstruction(op);
    if (p == NULL) {
      nbErreurs++;
      fprintf(stderr,ERR_CODOP_INCONNU, numero, op);
      fprintf(lst,ERR_CODOP_INCONNU, numero, op);
    } else {
      mots[nbMots] = p->codeOperation;
      if (p->masque != 0) {
	if (strcmp(arg,"") == 0) {
	  nbErreurs++;
	  fprintf(stderr, ERR_ARGUMENT_MANQUANT,  numero, op);
	  fprintf(lst, ERR_ARGUMENT_MANQUANT,  numero, op);

	} else {
	  if (estNombre(arg)) {
	    mots[nbMots] += atoi(arg) & p->masque ;
	  } else {
	    // on suppose que c'est un identificateur
	    ajouterReference(arg,numero,nbMots,
			     p->masque);
	  }
	}
	nbMots++;
      }
    }
  }
}

// ------------------------------------------------------------

bool caractereValideDansSymbole(char c) 
{
  if (c == '\0')
    return false;
  return isalnum(c)
      || (strchr(caracteresDansSymbole,c) != NULL);
}

// ------------------------------------------------------------

void assemblerSource() 
{
  int numeroLigne = 0;
  char * ligne = NULL;
  size_t taille = 0;

  nbMots = 0;
  initialiserTableDesSymboles();

  fprintf(lst,
	  "***************\n"
	  "* Code source *\n"
	  "***************\n\n");

  while ( getline(&ligne, &taille, src) >= 0) {
    char *pl = ligne;
    char tampon [taille];
    char *pt = tampon;

    *pt = '\0';        
    numeroLigne ++;
    char *i = strchr(ligne, '\n');
    if (i != NULL) 
      *i = '\0';
    fprintf(lst, "%3d :\t%s\n" , numeroLigne, ligne); // ligne source

    // élimination de commentaire éventuel
    i = strchr(ligne, '#');
    if (i != NULL) 
      *i = '\0';

    char *label = NULL, 
      *op = NULL,
      *arg = NULL;

    *pt = '\0';
    label = pt;

    if (caractereValideDansSymbole(*pl)) { // etiquette
      do {
	*pt++ = *pl++;
      }  while (caractereValideDansSymbole(*pl));
    }
    *pt++ = '\0';

    // printf("1. label=%s\n", label);
    while (isspace(*pl))  // espaces avant op
      pl++;
    
    op = pt;
    *pt = '\0';
    if (caractereValideDansSymbole(*pl)) { // etiquette
      do {      
	*pt++ = *pl++;
      }  while (caractereValideDansSymbole(*pl));
    }
    *pt++ = '\0';
 
    // printf("2. label=%s op=%s\n", label, op);
    while (isspace(*pl))  // espaces après op
      pl++;

    arg = pt;
    *pt = '\0';
    if ( (*pl == '-') || isdigit(*pl)) {   // nombre
      do {
	*pt++ = *pl++;
      } while (isdigit(*pl));
    } else { 
      while(caractereValideDansSymbole(*pl)) // identificateur
	*pt++ = *pl++;
    }
    *pt++ = '\0';
    // printf("3. label=%s op=%s arg=%s\n", label, op, arg);
    assemblerInstruction(numeroLigne,label,op,arg);
  }
  free (ligne);
  resoudreReferences();
  afficherSymboles();
  afficherCode();
  fprintf(lst,ERR_ERREURS,nbErreurs);
  if (nbErreurs == 0) {
    genererFichierHexa();
  } else {
    fprintf(stderr,ERR_ABANDON, nbErreurs);
  }
}

// ----------------------------------------------------------
  
void afficheUsage(char prog[])
{
  printf("Usage : %s [-h] fichier.asm\n"
	"Assemble le fichier.asm sous forme de fichier.hex"
	"Options:\n"
	"  -h  help\n"
	, prog);
}

int main(int argc, char *argv[])
{
  bool h_flag = false;   // help
  int c;
  opterr = 0;
     
  while ((c = getopt (argc, argv, "h")) != -1)
    switch (c) {
           case 'h':
	     h_flag = true;
             break;
           case '?':
	     if (isprint (optopt))
               fprintf (stderr, ERR_OPT_INCONNUE, optopt);
             else
               fprintf (stderr, ERR_OPT_CAR_INCONNU, optopt);
	     afficheUsage(argv[0]);
             return EXIT_FAILURE;
           default:
             abort ();
           }

   if (h_flag) {
     afficheUsage(argv[0]);
     return EXIT_SUCCESS;
   }

    int p = strlen(argv[1]) - 4;
    if (strcmp(argv[1]+p,".asm") != 0) {
      fprintf(stderr, ERR_SUFFIXE_ASM_ATTENDU);
      return EXIT_FAILURE;
    }

    src = fopen(argv[1], "r");
    if (! src) {
      fprintf(stderr, ERR_OUVERTURE_LECTURE, argv[1]); 
       return EXIT_FAILURE;
    }
    char prefixe[MAX_PATH_LEN];
    strncpy(prefixe,argv[1], p+1);
    prefixe[p] = '\0';

    char chemin_hex[MAX_PATH_LEN];
    strncpy(chemin_hex,argv[1], p+1);
    strcpy(chemin_hex+p,".hex");
    hex = fopen(chemin_hex, "w");
    if (! hex) {
      fprintf(stderr, ERR_OUVERTURE_ECRITURE, chemin_hex);
        return EXIT_FAILURE;
    }
    char chemin_lst[MAX_PATH_LEN];
    strncpy(chemin_lst,argv[1], p+1);
    strcpy(chemin_lst+p,".lst");
    lst = fopen(chemin_lst, "w");
    if (! lst) {
      fprintf(stderr, ERR_OUVERTURE_ECRITURE, chemin_lst);
        return EXIT_FAILURE;
    }

    trierTypesInstructions();
    assemblerSource();

    fclose(src);
    fclose(lst);
    fclose(hex);
    
    return EXIT_SUCCESS;
}

// - fin
