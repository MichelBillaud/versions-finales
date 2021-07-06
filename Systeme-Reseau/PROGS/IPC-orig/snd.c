/* IPC/snd.c */

/*
   envoi des messages dans une file (IPC System V)
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <stdbool.h>
#include <assert.h>

#define MAX_TEXTE 1000

struct Message {
    long mtype;
    char mtext[MAX_TEXTE];
};


int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s clé type\n", argv[0]);
        return EXIT_FAILURE;
    }
    int cle   = atoi(argv[1]);
    int mtype = atoi(argv[2]);

    int id    = msgget(cle, 0666);
    assert(id > 0);

    while (true) {
        struct Message message;
        printf("> ");
        fgets(message.mtext, MAX_TEXTE, stdin);
        message.mtype = mtype;

        int l = strlen(message.mtext);
        assert( msgsnd(id, & message, l + 1, 0)  == 0);
    }
}
