#include <stdio.h>
#include <stdlib.h>

#include "ens_chaines.h"

int main()
{
    struct ens_chaines ensemble;
    ec_init(& ensemble);

    char *mots[] = {
        "un", "deux", "trois", "un",
        "quatre", "deux", "cinq", "six",
        "sept", "trois", "huit", "neuf",
        "dix", "trois", "sept",
        NULL
    };
    for (int i = 0; mots[i] != NULL; i++) {
        ec_ajouter(& ensemble, mots[i]);
    }

    printf("-> taille %d (attendu = 10)\n",
            ec_taille(& ensemble));
    
    ec_dump(& ensemble);
    ec_liberer(& ensemble);

    return EXIT_SUCCESS;
}
