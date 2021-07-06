/* Divers/sig-posix.c */

#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

#define DELAI          1	/*secondes */
#define NB_ITERATIONS 60

void traiter_signal(int numero_signal)
{
    struct sigaction rien, ancien_traitement;

    printf("Signal %d => ", numero_signal);

    switch (numero_signal) {
    case SIGTSTP:
        printf("J'ai reçu un SIGTSTP.\n");

        /* on désarme le signal SIGTSTP, avec sauvegarde de
           du "traitant" précédent */
        rien.sa_handler = SIG_DFL;
        rien.sa_flags = 0;
        sigemptyset(&rien.sa_mask);	/* rien à masquer */
        sigaction(SIGTSTP, &rien, &ancien_traitement);

        printf("Alors je m'endors....\n");
        kill(getpid(), SIGSTOP);	/* auto-endormissement */
        printf("On me réveille ?\n");

        /* remise en place ancien traitement */
        sigaction(SIGTSTP, &ancien_traitement, NULL);
        printf("C'est reparti !\n");
        break;
    case SIGINT:
    case SIGTERM:
        printf("On m'a demandé d'arrêter le programme.\n");
        exit(EXIT_SUCCESS);
        break;
    }
}

int main(void)
{
    struct sigaction action;

    action.sa_handler = traiter_signal;	/* fonction à lancer */
    sigemptyset(&action.sa_mask);	/* rien à masquer */

    sigaction(SIGTSTP, &action, NULL);	/* pause contrôle-Z */
    sigaction(SIGINT,  &action, NULL);	/* fin contrôle-C */
    sigaction(SIGTERM, &action, NULL);	/* arrêt */


    for (int i = 1; i < NB_ITERATIONS; i++) {
        sleep(DELAI);
        printf("%d", i % 10);
        fflush(stdout);
    }

    printf("Fin\n");
    return EXIT_SUCCESS;
}
