//      Simulateur

#include <stdio.h>
#include <stdlib.h>

#include "machine.h"
#include "entrees-sorties.h"
#include "execution.h"

int main(int argc, char **argv)
{
     struct Machine m;
     printf("* Simulateur v1.0\n");

     if (argc != 2) {
          fprintf(stderr, "Usage: %s fichier\n", argv[0]);
          return EXIT_FAILURE;
     }
     charger_fichier(&m, argv[1]);
     lancer_execution(&m);
     afficher_etat(&m);

     printf("* Bye.\n");
     return EXIT_SUCCESS;
}

