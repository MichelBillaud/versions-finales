
struct Reference {
  int ligne;
  int position;
  int masque;
};


struct Symbole {
  char * nom;
  int ligne;
  int valeur;
  int maxRef, nbRef ;   // tableau extensible
  struct Reference * tRef;
};

extern void * 
tableDesSymboles;

void 
initialiserTableDesSymboles();

struct Symbole *  
creerSymbole(char nom[]) ;

struct Symbole * 
chercherSymbole(char nom[]);

bool 
symboleEstDefini(char * nom);

void 
definirSymbole(char nom[], int ligne, int valeur);

void 
ajouterReference(char nom[], int ligne, int position, int masque);
