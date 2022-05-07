#include <search.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

struct Voiture  {
  char * plaque;
  char * modele;
  int annee;
};

char *strdup(const char *s);

struct Voiture * makeMyCar(char *p, char *m, int a)
{
    struct Voiture * pv = 
        (struct Voiture *)calloc(sizeof(struct Voiture),1);
    pv -> plaque = strdup(p);
    pv -> modele = strdup(m);
    pv -> annee  = a;
    return pv;
}
void afficher(char m[], const struct Voiture *v) {
  printf("%s : plaque=%s, modele=%s, annee=%d\n",
	 m, v->plaque, v->modele, v->annee);
}

int comparaison(const void *a, const void *b)
{
  const struct Voiture *va = (const struct Voiture *) a;
  const struct Voiture *vb = (const struct Voiture *) b;
  return strcasecmp(va->plaque, vb->plaque);
}

void action(const void *nodep, 
	    const VISIT type, 
	    const int profondeur)
{
  const struct Voiture *v = *(struct Voiture **)  nodep;
  switch (type) {
  case postorder:
    afficher("postorder", v);
    break;
  case leaf:
    afficher("leaf", v);
    break;
  case preorder:
  case endorder:
    break;
  }
}

int main(void)
{
  struct Voiture *v;
  struct Voiture *v1 = makeMyCar("123AB33", "Peugeot 104", 1989);
  struct Voiture *v2 = makeMyCar("55AA33", "Peugeot 401", 1969);
  struct Voiture *v3 = makeMyCar("45XY79", "Citroen DS", 1965);
  struct Voiture *v4 = makeMyCar("76X23", "Renault R4", 1979);

  void * parking = NULL;
  
  printf("premiere insertion\n");

  struct Voiture ** ret = NULL;
  ret = tsearch( v1, &parking, comparaison);
  if (ret == NULL) {
    printf("*erreur* premier search renvoit NULL\n");
  }
  v = * ret;
  afficher("apres tsearch", v);
  // afficher(v1);
  tsearch( v2, &parking, comparaison);
  tsearch( v3, &parking, comparaison);
  tsearch( v4, &parking, comparaison);

  struct Voiture *requete = makeMyCar("45XY79", "xxxx", 0);

  ret = tsearch(requete, &parking, comparaison);
  if (ret == NULL) {
    printf("non trouve\n");
  } else {
    afficher("recherche",*ret);
  }
  twalk(parking,action);
  return 0;
}
