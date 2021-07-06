// Signaux/sig-unix.c */

#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

#define DELAI  1	// secondes

bool continuer = true;

void traiter_signal(int numero_signal);

int main(void)
{
    signal(SIGTSTP, traiter_signal);	// si on reçoit contrôle-Z
    signal(SIGINT,  traiter_signal);	// si contrôle-C
    signal(SIGTERM, traiter_signal);	// si kill processus

    while (continuer) {
        sleep(DELAI);
        printf(".");
        fflush(stdout);
    }
    printf("fin\n");
    exit(EXIT_SUCCESS);
}

void traiter_signal(int numero_signal)
{
    printf("Signal %d => ", numero_signal);
    switch (numero_signal) {
    case SIGTSTP:
        printf("Je m'endors....\n");
        kill(getpid(), SIGSTOP);	   //  auto-endormissement

	// Bloqué ici. On repart si on reçoit SIGCONT

        printf("Je me réveille !\n");
        signal(SIGTSTP, traiter_signal);   //  repositionnement du traitement
        break;
    case SIGINT:
    case SIGTERM:
	    continuer = false;
        break;
    }
}
