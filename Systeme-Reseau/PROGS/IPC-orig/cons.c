/* IPC/cons.c */

/*
   Ce programme affiche périodiquement le contenu de la
   mémoire partagée. Arrêt par Contrôle-C
*/

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <stdbool.h>

#include <assert.h>

#define DELAI 2

void preparer_signaux();
void arreter_boucle();

struct Donnees {
    int nb;
    int total;
};

bool continuer_boucle = true;

int id_segment_partage();

int main(void)
{
    preparer_signaux();

    int id = id_segment_partage();

    struct Donnees *adr_donnees = shmat(id, NULL, SHM_R);
    assert (adr_donnees != NULL);

    continuer_boucle = true;
    while (continuer_boucle) {
        sleep(DELAI);
        printf("sous-total %d= %d\n",
               adr_donnees->nb,
               adr_donnees->total);
    }
    printf("---\n");

    assert (shmdt(adr_donnees) != -1);

    return EXIT_SUCCESS;
}

void arreter_boucle(/* int signal */)
{
    continuer_boucle = false;
}


int id_segment_partage()
{
    key_t cle = ftok(getenv("HOME"), 'A');
    assert(cle != -1);

    int id = shmget(cle, sizeof(struct Donnees), 0);;
    if (id == -1) {
        switch (errno) {
        case ENOENT:
            printf("pas de segment\n");
            break;
        default:
            printf("erreur ouverture segment\n");
            break;
        }
        exit(EXIT_FAILURE);
    }
    return id;
}

void preparer_signaux()
{
    struct sigaction action = {
	.sa_handler = arreter_boucle,
	.sa_flags = 0
    };
    sigemptyset(&action.sa_mask);
  
    sigaction(SIGINT, &a, NULL);
}
