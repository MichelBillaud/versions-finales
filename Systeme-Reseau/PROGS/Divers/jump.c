/* Divers/jump.c */

#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum {                            // définitions de constantes
    PAS_DE_SOLUTION = 1,
    EQUATION_TRIVIALE = 2
};

float solution_equation(float a, float b);
void traiter_des_equations();

jmp_buf debut_de_main;

int main(void)
{
    int code_retour = setjmp(debut_de_main);
    if ( code_retour == 0 ) {  // toujours 0 après l'appel
        traiter_des_equations();
        return EXIT_SUCCESS;
    }

    // si != 0, c'est que le déroulement a appelé longjmp
    // qui a fait revenir au setjmp.
    switch (code_retour) {
    case PAS_DE_SOLUTION:
        printf("Cette équation n'a pas de solution_equation\n");
        break;
    case EQUATION_TRIVIALE:
        printf("Cette équation est toujours vraie.\n");
        break;
    }
    return EXIT_FAILURE;
}

float solution_equation(float a, float b)
{
    if (a == 0.0) {
        if (b == 0.0 ) {
            longjmp(debut_de_main, EQUATION_TRIVIALE);
        } else {
            longjmp(debut_de_main, PAS_DE_SOLUTION);
        }
    };
    return ( -b / a);
}

void traiter_des_equations()
{
    while (true) {
        printf("Coefficients de ax+b=0\n");
        float a,b;
        scanf("%f %f", &a, &b);
        float x = solution_equation(a,b);
        printf("x=%f est solution de %f x + %f = 0\n",
               x, a, b);
    }
}

