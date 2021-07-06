/* Threads/leger_mutex.c */

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

struct DonneesTache {
    char * chaine;    // chaine à écrire
    int nombre;       // nombre de répétitions
    int delai;        // délai entre écritures
};

int dernier_numero = 0;   //  variable accédée par les threads 
pthread_mutex_t verrou;   //  protège l'accès à la variable numero 

int nouveau_numero();
void * executer_tache(void * ptr);

int main(void)
{
    // verrou partagé entre les threads
    pthread_mutex_init(&verrou, NULL);

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

    pthread_mutex_destroy(&verrou);

    return EXIT_SUCCESS;
}

/**
 * Retourne un nouveau numéro, en utilisant un mutex pour
 * protéger la section critique.
 * @return un numéro
 */

int nouveau_numero()
{
    pthread_mutex_lock(&verrou);   // début section critique
    int n = ++dernier_numero;
    pthread_mutex_unlock(&verrou); // fin section critique
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
