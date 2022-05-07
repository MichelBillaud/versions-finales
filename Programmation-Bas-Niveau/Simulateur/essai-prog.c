#include <search.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PATH_LEN 1024

FILE * src;
FILE * hex;
FILE * lst;


void assemblerSource() {
  int numero = 0;
  char * ligne = NULL;
  size_t taille = 0;

  while ( getline(&ligne, &taille, src) >= 0) {
    numero ++;
    char *i = strchr(ligne, '\n');
    if (i) *i = '\0';
    printf("%3d : %s\n" , numero, ligne);

    int dlabel, flabel, dop, fop, darg, farg;	
    dlabel = flabel = 0;
    while (isalnum(ligne[flabel]))
      flabel ++;
    
    char * label = strndup(ligne+dlabel, flabel-dlabel);
    label[flabel-dlabel] = '\0';
    // printf("label = '%s'\n", label);
    
    dop = flabel;
    while(isspace(ligne[dop])) 
      dop ++;
    fop = dop;
    while(isalnum(ligne[fop])) 
      fop++;
    char * op = strndup(ligne+dop, fop-dop);
    op[fop-dop] = '\0';
    
    // printf("op    = '%s'\n", op);
    
    darg = fop;
    while(isspace(ligne[darg])) 
      darg ++;
    farg = darg;
    while(isalnum(ligne[farg])) 
      farg++;
    char * arg = strndup(ligne+darg, farg-darg);
    arg[farg-darg] = '\0';
    // printf("arg    = '%s'\n", arg);
  }
  free (ligne);
}

int main (int argc, char * argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s source.asm", argv[0]);
        return EXIT_FAILURE;
    }

    int p = strlen(argv[1]) - 4;
    if (strcmp(argv[1]+p,".asm") != 0) {
        fprintf(stderr,
                "Erreur: le nom du source doit se termine par .asm\n");
        return EXIT_FAILURE;
    }

    src = fopen(argv[1], "r");
    if (! src) {
        fprintf(stderr, "Erreur: ne peut pas ouvrir '%s' en lecture*\n",
                argv[1]);
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
        fprintf(stderr, "Erreur: ne peut pas ouvrir '%s' en ecriture\n",
                chemin_hex);
        return EXIT_FAILURE;
    }
    char chemin_lst[MAX_PATH_LEN];
    strncpy(chemin_lst,argv[1], p+1);
    strcpy(chemin_lst+p,".lst");
    lst = fopen(chemin_lst, "w");
    if (! lst) {
        fprintf(stderr, "Erreur: ne peut pas ouvrir '%s' en ecriture\n",
                chemin_lst);
        return EXIT_FAILURE;
    }

    assemblerSource();

    /* dÃ©coupage de la ligne */
    fclose(src);
    fclose(lst);
    fclose(hex);
    return EXIT_SUCCESS;
}
