// ens_chaines.h

#ifndef ENS_CHAINE_H
#define  ENS_CHAINE_H

struct ens_alveole;            // prédéclaration

struct ens_chaines {
    int nb_alveoles;
    int nb_elements;
    struct ens_alveole *alveoles;
};


void ec_init   (struct ens_chaines *e);
void ec_ajouter(struct ens_chaines *e, const char *chaine);

int ec_taille  (const struct ens_chaines *e);
void ec_dump   (const struct ens_chaines *e);

void ec_liberer(struct ens_chaines *e);

#endif
