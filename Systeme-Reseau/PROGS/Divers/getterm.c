/* Divers/getterm.c */

#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    char *terminal = getenv("TERM");

    printf("Le terminal est ");
    if (terminal == NULL) {
        printf("inconnu\n");
    } else {
        printf("un %s\n", terminal);
    }
    return EXIT_SUCCESS;
}
