/* IPC/sem.c */

/*
   Opérations sur des sémaphores
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>


typedef int SEMAPHORE;          // identifiant de sémaphore

void detruire_sem(SEMAPHORE sem)
{
    assert(semctl(sem, 0, IPC_RMID, 0) == 0);
}

void changer_sem(SEMAPHORE sem, int val)
{
    struct sembuf sb[1];
    sb[0].sem_num = 0;
    sb[0].sem_op = val;
    sb[0].sem_flg = 0;
    assert(semop(sem, sb, 1) == 0);
}

SEMAPHORE creer_sem(key_t key)
{
    SEMAPHORE sem = semget(key, 1, IPC_CREAT | 0666);
    assert(sem >= 0);
    assert(semctl(sem, 0, SETVAL, 0) >= 0); /* valeur initiale = 0 */
    return sem;
}

void P(SEMAPHORE sem)
{
    changer_sem(sem, -1);
}

void V(SEMAPHORE sem)
{
    changer_sem(sem, 1);
}

/* --------------------------------------------- */

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s cle\n", argv[0]);
        return EXIT_FAILURE;
    }
    key_t key = atoi(argv[1]);
    SEMAPHORE sem = creer_sem(key);

    bool encore = true;
    while (encore) {
        char reponse;
        printf("p,v,x,q ? ");
        if (scanf("%c", &reponse) != 1)
            break;
        switch (toupper(reponse)) {
        case 'P':
            P(sem);
            printf("OK.\n");
            break;
        case 'V':
            V(sem);
            printf("OK.\n");
            break;
        case 'X':
            detruire_sem(sem);
            printf("Sémaphore détruit\n");
            encore = 0;
            break;
        case 'Q':
            encore = false;
            break;
        default:
            printf("?\n");
        }
    }
    printf("Bye.\n");
    return EXIT_SUCCESS;
}
