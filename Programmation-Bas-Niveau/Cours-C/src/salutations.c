#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    printf("Ceci est le programme %s avec %d arguments.\n",
           argv[0], argc);
    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    return EXIT_SUCCESS;
}
