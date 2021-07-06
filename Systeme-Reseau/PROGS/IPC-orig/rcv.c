/* IPC/rcv.c */

/*
   affiche les messages qui proviennent
   d'une file (IPC System V)
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdbool.h>
#include <assert.h>

#define MAX_TEXTE 1000

struct Message {
    long mtype;
    char mtext[MAX_TEXTE];
};

bool continuer_boucle = true;

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s cle\n", argv[0]);
        return EXIT_FAILURE;
    }
    int cle = atoi(argv[1]);
    int id = msgget(cle, IPC_CREAT | 0666);
    assert(id != -1);

    while (continuer_boucle) {
        struct Message message;
        int l = msgrcv(id, &message, MAX_TEXTE, 0L, 0);
        assert (l != -1);
        printf("(type=%ld) %s\n",
               message.mtype, message.mtext);
    }

    return EXIT_SUCCESS;
}
