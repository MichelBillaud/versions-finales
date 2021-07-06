/* Divers/getlang.c */

#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    const char *variable_lang = getenv("LANG");

    printf("La variable d'environnement LANG ");
    if (variable_lang == NULL) {
        printf("n'est pas définie\n");
    } else {
        printf("contient \"%s\".\n", variable_lang);
    }
    return EXIT_SUCCESS;
}
