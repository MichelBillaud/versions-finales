#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>

// Pour emacs :
// Local Variables:                                                   
// compile-command: "LANG=C gcc -std=c99 -Wall -Wextra options.c -o options"  
// End:                                                          

#define UNUSED(x) (void)(x)

/*
  options prévues:  -[ti] fichier.hex
  -t trace
  -i interactive
*/

void afficheUsage(char prog[])
{
  printf("Usage : %s [-i][-t][-h] fichier.hex\n"
	"Charge le fichier.hex dans la mémoire du simulateur\n"
	"et lance l'exécution\n"
	"Options:\n"
	"  -i  simulation interactive\n"
	"  -t  fonctionnement interactif\n"
	"  -h  help\n"
	, prog);
}
int main(int argc, char *argv[])
{
  bool 
    t_flag = false,   // trace
    i_flag = false,   // interactive mode
    h_flag = false;   // help
  int c;
  opterr = 0;
     
  while ((c = getopt (argc, argv, "tih")) != -1)
    switch (c) {
           case 't':
             t_flag = true;
             break;
           case 'i':
             i_flag = true;
             break;
           case 'h':
	     h_flag = true;
             break;
           case '?':
	     if (isprint (optopt))
               fprintf (stderr, "Option inconnue `-%c'.\n", optopt);
             else
               fprintf (stderr,
                        "Option inconnue `\\x%x'.\n",
                        optopt);
	     afficheUsage(argv[0]);
             return EXIT_FAILURE;
           default:
             abort ();
           }

  printf("Flags: trace=%d, interactive=%d, help=%d\n",
	 t_flag, i_flag, h_flag);

  for (int index = optind; index < argc; index++)
     printf ("Autre argument: %s\n", argv[index]);

   if (h_flag) {
     afficheUsage(argv[0]);
     return EXIT_SUCCESS;
   }

  return EXIT_SUCCESS;
}
