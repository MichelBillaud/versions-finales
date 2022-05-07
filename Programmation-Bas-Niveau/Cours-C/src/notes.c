/*
  Lecture d'un fichier de notes
  Affichage du nombre de notes, de la somme, et de la moyenne.
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    float somme  = 0.0;
    int   nombre = 0;
    float note;

    FILE *fnotes = fopen("notes.txt", "r");

    while ( fscanf(fnotes, "%f", & note) == 1) {
        somme += note;
        nombre += 1;
    }

    fclose(fnotes);

    printf("%d notes lues, total=%.2f, moyenne=%05.2f\n",
           nombre, somme, somme/nombre);

    return EXIT_SUCCESS;
}
