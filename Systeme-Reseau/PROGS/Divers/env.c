/*
 * Divers/env.c
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    printf("Appel avec %d paramètres\n", argc);

    for (int k = 0; k < argc; k++) {
        printf("%d: %s\n", k, argv[k]);
    }

    return EXIT_SUCCESS;
}
