/*
 * Ecrit en c11, avec extensions POSIX
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <inttypes.h>
#include <stdbool.h>
#include <ctype.h>
#include <search.h>

#include "table-des-symboles.h"

typedef uint16_t Mot;

typedef struct
{
  char *op;
  Mot codeOperation;
  int masque;
} descDirective;

#define MAX_PATH_LEN 1024

FILE *src;
FILE *hex;
FILE *lst;

#define INDIRECT 0x800

descDirective Directives[] =
    {
        {"ld", 0x0000, 0x0FFF},
        {"ld", 0x0000 | INDIRECT, 0x0FFF},
        {"st", 0x1000, 0x0FFF},
        {"st*", 0x1000 | INDIRECT, 0x0FFF},
        {"add", 0x2000, 0x0FFF},
        {"add*", 0x2000 | INDIRECT, 0x0FFF},
        {"sub", 0x3000, 0x0FFF},
        {"sub*", 0x3000 | INDIRECT, 0x0FFF},
        {"cmp", 0x4000, 0x0FFF},
        {"cmp*", 0x4000 | INDIRECT, 0x0FFF},
        {"jmp", 0x5000, 0x0FFF},
        {"jmp*", 0x5000 | INDIRECT, 0x0FFF},
        {"call", 0x6000, 0x0FFF},
        {"call*", 0x6000 | INDIRECT, 0x0FFF},

        {"li", 0x7000, 0x0FFF},
        {"cmpi", 0x7800, 0x0FFF},

        {"halt", 0xF000, 0x0000},
        {"if", 0xF100, 0x000F},
        {NULL, 0, 0}

};

int numeroDirective(char op[])
{
  for (int i = 0; Directives[i].op != NULL; i++)
    if (strcasecmp(op, Directives[i].op) == 0)
      return i;
  return -1;
}

bool estNombre(char s[])
{
  int i = (s[0] == '-' ? 1 : 0);
  while (isdigit(s[i]))
    i++;
  return (s[i] == '\0');
}

Mot mots[1024];
int nbMots = 0;

int nbErreurs = 0;

void debutAssemblage()
{
  initialiserTableDesSymboles();
  nbMots = 0;
}

void visiterSymbole(const void *ptr,
                    const VISIT type,
                    const int profondeur)
{
  const struct Symbole *s = *(struct Symbole **)ptr;
  if (type == postorder || type == leaf)
  {
    printf("nom=%s,\tligne=%d,\tvaleur=%d :",
           s->nom, s->ligne, s->valeur);
    for (int i = 0; i < s->nbRef; i++)
    {
      printf("%d ", s->tRef[i].ligne);
    }
    printf("\n");
    if (s->ligne < 0)
    {
      fprintf(stderr, "Erreur : symbole %s non defini (lignes", s->nom);
      nbErreurs++;
      for (int i = 0; i < s->nbRef; i++)
      {
        fprintf(stderr, " %d", s->tRef[i].ligne);
      }
      fprintf(stderr, ")");
    }
    else
    {
      // appliquer les rustines
      for (int i = 0; i < s->nbRef; i++)
      {
        mots[s->tRef[i].position] |= (s->valeur & s->tRef[i].masque);
      }
    }
  }
}

void finAssemblage()
{
  printf("Segment mémoire avant rustines : \n");
  for (int i = 0; i < nbMots; i++)
  {
    printf("%03x:  %04x   (%d)\n", i, mots[i], mots[i]);
  }
  twalk(tableDesSymboles, visiterSymbole);
  printf("Segment mémoire apres rustines : \n");
  for (int i = 0; i < nbMots; i++)
  {
    printf("%03x:  %04x   (%d)\n", i, mots[i], mots[i]);
  }

  if (nbErreurs != 0)
bool ends_with(const char string[], const char suffix[]) {
  int string_length = strlen(string);
  int suffix_length = strlen(suffix);
  return strcmp(string_le)
}
  {
    fprintf(stderr, "%d erreur(s). Abandon.\n", nbErreurs);
    return;
  }
  // sortie fichier hexa
  for (int i = 0; i < nbMots; i++)
  {
    fprintf(hex, "%04x ", mots[i]);
    if (i % 8 == 7)
      fprintf(hex, "\n");
  }
  fprintf(hex, "\n");
}

void assemblerInstruction(int numero,
                          char label[], char op[], char arg[])
{
  /* printf("assemblage ligne %d : label = '%s', op='%s', arg='%s'\n",
           numero, label, op, arg);
  */
  if (strcmp(label, "") != 0)
  {
    // ajout de définition de symbole
    struct Symbole *l = chercherSymbole(label);
    if (l->ligne >= 0)
    {
      printf("ERREUR ligne %d: Symbole %s déjà défini ligne %d\n",
             numero, label, l->ligne);
    }
    else
    {
      l->ligne = numero;
      l->valeur = nbMots;
    }
  }

  if (strcmp(op, "") == 0)
  {
    return;
  }

  if (strcasecmp(op, "word") == 0)
  {
    int valeur = 0;
    if (estNombre(arg))
    {
      printf("%s est un nombre\n", arg);
      valeur = atoi(arg);
    }
    else
    {
      // on suppose que c'est un identificateur
      ajouterReference(arg, numero, nbMots, 0xFFF);
    }
    mots[nbMots++] = valeur;
  }
  else
  {
    int i = numeroDirective(op);
    if (i < 0)
    {
      printf("ERREUR: directive '%s' inconnue\n", op);
    }
    else
    {
      mots[nbMots] = Directives[i].codeOperation;
      if (Directives[i].masque != 0)
      {
        if (strcmp(arg, "") == 0)
        {
          printf("ERREUR ligne %d: argument attendu pour %s\n",
                 numero, op);
        }
        else
        {
          if (estNombre(arg))
          {
            printf("%s est un nombre\n", arg);
            mots[nbMots] += atoi(arg) & Directives[i].masque;
          }
          else
          {
            // on suppose que c'est un identificateur
            ajouterReference(arg, numero, nbMots,
                             Directives[i].masque);
          }
        }
        nbMots++;
      }
    }
  }
}

/* l'analyse syntaxique est un peu rustique, faut reconnaître */

char *caracteresDansSymbole = "_*-$";

bool caractereValideDansSymbole(char c)
{
  return isalnum(c) || strchr(caracteresDansSymbole, c);
}

void assemblerSource()
{
  int numeroLigne = 0;
  char *ligne = NULL;
  size_t taille = 0;

  debutAssemblage();
  while (getline(&ligne, &taille, src) >= 0)
  {
    numeroLigne++;
    char *i = strchr(ligne, '\n');
    if (i) {
      *i = '\0';
    }
    printf("%3d : %s\n", numeroLigne, ligne);

    int dlabel = 0, flabel = 0; // début et fin du label
    while (caractereValideDansSymbole(ligne[flabel])) {
      flabel++;
    }

    char *label = strndup(ligne + dlabel, flabel - dlabel);
    label[flabel - dlabel] = '\0';
    // printf("label = '%s'\n", label);

    int dop = flabel;       // début code opération
    while (isspace(ligne[dop])) {
      dop++;
    }
    int fop = dop;          // fin code opération
    while (caractereValideDansSymbole(ligne[fop])) {
      fop++;
    }

    char *op = strndup(ligne + dop, fop - dop);
    op[fop - dop] = '\0';
    // printf("op    = '%s'\n", op);

    int darg = fop;                  // début argument
    while (isspace(ligne[darg])) {
      darg++;
    }
    int farg = darg;                 // fin argument
    while (caractereValideDansSymbole(ligne[farg])) {
      farg++;
    }
    char *arg = strndup(ligne + darg, farg - darg);
    arg[farg - darg] = '\0';
    // printf("arg    = '%s'\n", arg);
    assemblerInstruction(numeroLigne, label, op, arg);
  }
  free(ligne);
  finAssemblage();
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    fprintf(stderr, "Usage: %s source.asm", argv[0]);
    return EXIT_FAILURE;
  }

  int p = strlen(argv[1]) - 4;
  if (strcmp(argv[1] + p, ".asm") != 0)
  {
    fprintf(stderr,
            "Erreur: le nom du source doit se termine par .asm\n");
    return EXIT_FAILURE;
  }

  src = fopen(argv[1], "r");
  if (!src)
  {
    fprintf(stderr, "Erreur: ne peut pas ouvrir '%s' en lecture*\n",
            argv[1]);
    return EXIT_FAILURE;
  }
  char prefixe[MAX_PATH_LEN];
  strncpy(prefixe, argv[1], p + 1);
  prefixe[p] = '\0';

  char chemin_hex[MAX_PATH_LEN];
  strncpy(chemin_hex, argv[1], p + 1);
  strcpy(chemin_hex + p, ".hex");
  hex = fopen(chemin_hex, "w");
  if (!hex)
  {
    fprintf(stderr, "Erreur: ne peut pas ouvrir '%s' en ecriture\n",
            chemin_hex);
    return EXIT_FAILURE;
  }
  char chemin_lst[MAX_PATH_LEN];
  strncpy(chemin_lst, argv[1], p + 1);
  strcpy(chemin_lst + p, ".lst");
  lst = fopen(chemin_lst, "w");
  if (!lst)
  {
    fprintf(stderr, "Erreur: ne peut pas ouvrir '%s' en ecriture\n",
            chemin_lst);
    return EXIT_FAILURE;
  }

  assemblerSource();

  fclose(src);
  fclose(lst);
  fclose(hex);
  return EXIT_SUCCESS;
}
