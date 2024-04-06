// ens-chaines.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ens_chaines.h"


struct ens_cellule {
    char * chaine;
    struct ens_cellule *suivant;
};

struct ens_alveole {
    struct ens_cellule *premier;
};


#define NOMBRE_MIN_ALVEOLES 4

void ec_init(struct ens_chaines *e)
{
    e->nb_elements = 0;
    e->nb_alveoles = NOMBRE_MIN_ALVEOLES;
    e->alveoles = malloc(e->nb_alveoles
                         * sizeof (struct ens_alveole));
}

static unsigned int ec_hash(const char * chaine)
{
    unsigned int hash = 0;
    for (const char *c = chaine; *c != '\0'; c++) {
        hash = 17 * hash + *c;
    }
    return hash;
}

static void ec_doubler_nb_alveoles(struct ens_chaines *e)
{
    int na = e->nb_alveoles; // avant agrandissement
    e->nb_alveoles *= 2;

    int taille =
        e->nb_alveoles * sizeof (struct ens_alveole);
    e->alveoles = realloc(e->alveoles, taille);


    // initialisation de nouvelles alvéoles
    for (int i = na; i < e->nb_alveoles; i++) {
        e->alveoles[i].premier = NULL;
    }

    // reclassement des éléments des anciennes alvéoles
    for (int i = 0; i < na; i++) {
        struct ens_cellule *premier
                = e->alveoles[i].premier;
        e->alveoles[i].premier = NULL;

        while (premier != NULL) {
            struct ens_cellule *c = premier;
            premier = premier->suivant;
            int num_alveole
                = ec_hash(c->chaine) % (e->nb_alveoles);
            struct ens_alveole *a
                = &( e->alveoles[num_alveole] );
            c->suivant = a->premier;
            a->premier = c;
        }
    }
}

void ec_ajouter(struct ens_chaines *e, const char *chaine)
{
    int num_alveole = ec_hash(chaine) % (e->nb_alveoles);
    struct ens_alveole * a = &(e->alveoles[num_alveole]);

    // sortie si déjà present
    for (struct ens_cellule *c = a->premier;
            c != NULL;
            c = c->suivant) {
        if (strcmp(c->chaine, chaine) == 0) {
            return;
        }
    }

    // Ajout nouvelle cellule avec copie de chaine
    struct ens_cellule *nc
        = malloc(sizeof (struct ens_cellule));
    nc->chaine = strdup(chaine);
    nc->suivant = a->premier;
    a->premier = nc;
    e->nb_elements += 1;

    // besoin d'agrandir ?
    if (e->nb_elements >= (3 * e->nb_alveoles) / 4) {
        ec_doubler_nb_alveoles(e);
    }
}

void ec_liberer(struct ens_chaines *e)
{
    for (int i = 0; i < e->nb_alveoles; i++) {
        struct ens_cellule *premier
                = e->alveoles[i].premier;
        while (premier != NULL) {
            struct ens_cellule *c = premier;
            premier = premier->suivant;
            free(c->chaine);
            free(c);
        }
    }
    free(e->alveoles);
    // par précaution
    e->nb_alveoles = 0;
    e->nb_elements = 0;
    e->alveoles = NULL;
}

int ec_taille(const struct ens_chaines *e)
{
    return e->nb_elements;
}

void ec_dump(const struct ens_chaines *e)
{
    for (int i = 0; i < e->nb_alveoles; i++) {
        printf("alvéole %2d ->", i);
        for (struct ens_cellule *c = e->alveoles[i].premier;
                c != NULL; c = c->suivant) {
            printf("\t\"%s\" (%u)",
                   c->chaine,
                   ec_hash(c->chaine));
        }
        printf("\n");
    }
}
