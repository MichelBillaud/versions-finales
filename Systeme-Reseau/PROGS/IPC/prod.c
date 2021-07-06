/* IPC/prod.c */

/*
   Ce programme lit une suite de nombres, et effectue le
   cumul dans une variable en mémoire partagée.
*/

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <assert.h>

struct Donnees {
    int nb;
    int total;
};

int id_nouveau_segment();

int main(void)
{
    int id = id_nouveau_segment();
    struct Donnees * adr_donnees
        = shmat(id, NULL, SHM_R | SHM_W);  // attachement au segment
    assert(adr_donnees != NULL);

    adr_donnees->nb = 0;
    adr_donnees->total = 0;

    while (true) {
        printf("+ ");
        int reponse;
        if (scanf("%d", &reponse) != 1) {
            break;
        }
        adr_donnees->nb++;
        adr_donnees->total += reponse;
        printf("sous-total %d= %d\n",
               adr_donnees->nb,
               adr_donnees->total);
    }

    assert (shmdt(adr_donnees) != -1);         // détachement
    assert (shmctl(id, IPC_RMID, NULL) != -1); // suppression

    printf("---\n");
    return EXIT_SUCCESS;
}

int id_nouveau_segment()
{
    key_t cle = ftok(getenv("HOME"), 'A');
    assert(cle != -1);

    int id = shmget(cle, sizeof(struct Donnees),  // création segment
                    IPC_CREAT | IPC_EXCL | 0666);
    if (id == -1) {
        switch (errno) {
        case EEXIST:
            printf("Note: le segment existe déjà\n");
            break;
        default:
            printf("Echec shmget\n");
            break;
        }
        exit(EXIT_FAILURE);
    }
    return id;
}
