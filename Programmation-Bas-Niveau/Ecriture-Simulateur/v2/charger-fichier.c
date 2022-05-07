#include <inttypes.h>

void charger_fichier (struct Machine *m, char chemin[])
{
     FILE *f;

     f = fopen(chemin, "r");
     if (f == NULL) {
          fprintf (stderr, "Le fichier %s ne peut être ouvert\n", chemin);
          return;
     }

     int position = 0;
     while ( fscanf(f, "%" SCNx16, & m -> M[position]) == 1) {
          position++;
     }
     printf("- Fichier %s : %d mots.\n", chemin, position);

     /* remplissage du reste avec des zeros */
     while (position < 256) {
          m->M[position++] = 0;
     }
     fclose(f);
}
