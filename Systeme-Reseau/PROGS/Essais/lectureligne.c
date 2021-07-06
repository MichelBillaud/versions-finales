#define  _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdlib.h>

int main()
{
    while(1) {
        char * line;
        printf("ligne :");
        scanf("%m[^\n]", &line);
        printf("=> '%s'\n", line);
        free(line);
    }

    return 0;
}

