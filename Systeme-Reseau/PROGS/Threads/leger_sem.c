/* Threads/leger.c */

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

struct DonneesTache {
    char * chaine;   // chaine à écrire
    int nombre;      // nombre de répétitions
    int delai;       // délai entre écritures
};

int   dernier_numero = 0;   // variable partagée par les threads
sem_t verrou;               // protège l'accès à la variable numero 

int nouveau_numero();
void * executer_tache(void * ptr);

int main(void)
{
    // Verrou partagé entre les threads, valeur initiale = 1
    sem_init(&verrou, 0, 1);

    struct DonneesTache donnees_tache_1 = {
        .nombre = 4,
        .chaine = "Hello",
        .delai = 2
    };
    struct DonneesTache donnees_tache_2 = {
        .nombre = 5,
        .chaine = "Hello",
        .delai = 1
    };

    pthread_t tache1, tache2;
    pthread_create(&tache1, NULL, executer_tache, &donnees_tache_1);
    pthread_create(&tache2, NULL, executer_tache, &donnees_tache_2);

    pthread_join(tache1, NULL);
    pthread_join(tache2, NULL);

    sem_destroy(&verrou);

    return EXIT_SUCCESS;
}

/**
 * Retourne un nouveau numéro, en protégeant la section critique
 * à l'aide d'un sémaphore.
 * @return  le numero
 */

int nouveau_numero()
{
    sem_wait(& verrou);              // début section critique
    int n = ++dernier_numero;
    sem_post(& verrou);              // fin section critique
    return n;
}

void * executer_tache(void * ptr)
{
    struct DonneesTache *adr_donnees  = ptr;

    for (int k = 0; k < adr_donnees->nombre ; k++) {
        int n = nouveau_numero();
        printf("[%d] %s\n", n, adr_donnees->chaine );

        sleep(adr_donnees->delai);
    };
    return NULL;
}
