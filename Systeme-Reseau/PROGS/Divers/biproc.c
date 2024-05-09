/* Divers/biproc.c */

/*
 * Illustration de fork() et pipe();
 *
 * Exemple à deux processus reliés par un tuyau
 - l'un envoie abcdef...z 10 fois dans le tuyau
 - l'autre écrit ce qui lui arrive du tuyau sur la
 sortie standard, en le formattant.
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>

#define TAILLE_LIGNE       30
#define TAILLE_ALPHABET    26
#define NOMBRE_REPETITIONS 10

void produire_donnees(int fd_sortie);
void consommer_donnees(int entree);
int lire_donnees(int fd_entree, char *tampon, size_t taille_tampon);

int main (void)
{
    int pipe_fils_pere[2];

    assert (pipe(pipe_fils_pere) == 0);

    pid_t pid_fils = fork();
    assert(pid_fils >= 0);

    if (pid_fils == 0) {
        /* le processus fils */
        close(pipe_fils_pere[0]);
        close(STDOUT_FILENO);
        produire_donnees(pipe_fils_pere[1]);
    } else {
        /* le processus père continue ici */
        close(STDIN_FILENO);
        close(pipe_fils_pere[1]);

        consommer_donnees(pipe_fils_pere[0]);

        int status;
        wait(&status);
        printf("status fils = %d\n", status);
    }
    return EXIT_SUCCESS;
}

void produire_donnees(int fd_sortie)
{
    char alphabet[TAILLE_ALPHABET];

    for (int k = 0; k < TAILLE_ALPHABET; k++) {
        alphabet[k] = 'a'+k;
    }

    for (int k = 0; k < NOMBRE_REPETITIONS; k++) {
        int nb_ecrits = write(fd_sortie, alphabet, TAILLE_ALPHABET);
        assert(nb_ecrits == TAILLE_ALPHABET);
    }
    close(fd_sortie);
}

int lire_donnees (int fd_entree, char *tampon, size_t taille_tampon)
{
    /* lecture, en insistant pour remplir le tampon */
    size_t deja_lus = 0;

    while (deja_lus < taille_tampon) {
        int n = read(fd_entree, tampon + deja_lus,
                     taille_tampon - deja_lus);
        if (n < 0) {
            return -1;
        }
        if (n == 0) {
            break; /* plus rien à lire */
        }
        deja_lus += n;
    }
    return deja_lus;
}

void consommer_donnees (int fd_entree)
{
    char ligne[TAILLE_LIGNE+1];
    int taille, numero_ligne = 1;

    while ((taille = lire_donnees(fd_entree,
                                  ligne, TAILLE_LIGNE)) > 0) {
        ligne[taille] = '\0';
        printf("%3d %s\n", numero_ligne++, ligne);
    };
    assert(taille >= 0);
    close(fd_entree);
}
