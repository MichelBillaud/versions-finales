/* Divers/essai-getopt.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

//  -h et -x sont de simples "switchs"
//  -a requiert un paramètre (:)

#define SPECIFICATION_OPTIONS  "hxa:"

void afficher_aide(const char prog[]); // déclaration avant usage

int main(int argc, char *argv[])
{
    bool  option_x_presente = false;
    char *argument_option_a = NULL;

    int   code = EXIT_SUCCESS;
    bool  options_restantes = true;

    do {
        int c = getopt(argc, argv, SPECIFICATION_OPTIONS);
        switch (c) {
        case -1 :
            options_restantes = false;
            break;
        case 'h':
            afficher_aide(argv[0]);
            break;
        case 'x':
            option_x_presente = true;
            break;
        case 'a' :
            argument_option_a = optarg;             // optional argument
            break;
        case '?':
            fprintf(stderr, "Option inconnue `-%c'.\n",
                    optopt);                // option char
            code = EXIT_FAILURE;
            break;
        default:
            code = EXIT_FAILURE;
        }
    } while(options_restantes);

    printf("= option `-x' %s\n",
           (option_x_presente ? "activée" : "désactivée"));

    if (argument_option_a == NULL) {
        printf("= paramètre `-a' absent\n");
    } else {
        printf("= paramètre `-a' présent = %s\n", argument_option_a);
    }

    printf("%d paramètres supplémentaires\n",
           argc - optind);                    // option index
    for (int k = optind; k < argc; k++)
        printf ("    ->  %s\n", argv[k]);

    return code;
}

void afficher_aide(const char prog[])         // définition
{
    printf("Help:  %s [options...] parametres ... \n\n",
           prog);
    printf("Options:\n"
           "-h\tCe message d'aide\n"
           "-x\toption x\n"
           "-a nom\t paramètre optionnel\n");
}
