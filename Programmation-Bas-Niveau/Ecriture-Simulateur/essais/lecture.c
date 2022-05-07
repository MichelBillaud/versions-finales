/*
 * lecture dans un fichier
 */

#include <stdio.h>
#include <stdlib.h>

/* lit et affiche des nombres */
void lire_nombres(char chemin[])
{
     FILE *f;
     f = fopen(chemin, "r");
     if (f == NULL) {
          fprintf (stderr, "Le fichier %s ne peut être ouvert\n", chemin);
          return;
     }
     int nombre;
     while ( fscanf(f, "%d", & nombre) == 1) {
          printf ("%d ", nombre);
     }
     printf("\n");
     fclose(f);
}

int main(int argc, char **argv)
{
     if (argc != 2) {
          fprintf (stderr, "usage: %s fichier\n", argv[0]);
          return EXIT_FAILURE;
     }
     lire_nombres(argv[1]);
     return EXIT_SUCCESS;
}

