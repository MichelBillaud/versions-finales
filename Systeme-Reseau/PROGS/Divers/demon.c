/* Divers/demon.c */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int devenir_demon(void)
{
    /* Le processus se dédouble, et le père se termine */
    if (fork() != 0) {
        exit(EXIT_SUCCESS);
    }

    /* le processus fils devient le leader d'un nouveau
       groupe de processus */
    setsid();

    /* le processus fils crée le processus démon, et
       se termine */
    if (fork() != 0) {
        exit(EXIT_SUCCESS);
    }

    /* le démon déménage vers la racine */
    chdir("/");

    /* l'entrée standard est redirigée vers /dev/null */
    int fd = open("/dev/null", O_RDWR);
    dup2(fd, STDIN_FILENO);
    close(fd);

    /* et les sorties vers /dev/console */
    fd = open("/dev/console", O_WRONLY);
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);
    close(fd);
    return EXIT_SUCCESS;
}
