/* Essais/test-waitpid.c */

/*
 * essais avec wait pid;
 *
 * Lance un processus fils qui boucle
 * affiche son numéro
 * surveille son état avec waitpid.
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>

void travail()
{
    while (true) {
        sleep(1);
    }
}

int main(void)
{
    printf("Lancement\n");
    pid_t pid_fils = fork();

    if (pid_fils == 0) {
        /* le processus pid_fils */
        close (STDIN_FILENO);
        close (STDOUT_FILENO);
        travail();
    }
    printf("* envoyez des signaux au processus %d\n", pid_fils);

    bool fini = false;
    do {
        int status;
        waitpid(pid_fils, &status, 0);

        if (WIFEXITED(status)) {
            printf("fin normale, status = %d\n",
                   WEXITSTATUS(status));
            fini = true;
        }
        if (WIFSIGNALED(status)) {
            printf("terminé à cause signal %d\n",
                   WTERMSIG(status));
            fini = true;
        }
        if (WIFSTOPPED(status)) {
            printf("stoppé à cause signal %d\n",
                   WSTOPSIG(status));
        }
        if (WIFCONTINUED(status)) {
            printf("continué\n");
        }
    } while (! fini);
    return EXIT_SUCCESS;
}
