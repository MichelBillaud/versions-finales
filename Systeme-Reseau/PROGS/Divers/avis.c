/* Divers/avis.c */

/* Illustration de popen() */

#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>

#define TAILLE_MAX_COMMANDE 100


void envoyer_mail(const char *mail_destinataire);
void fabriquer_message_liste_fichiers(FILE *sortie);


int main (int argc, char * argv[])
{
    if (argc != 2) {
        fprintf(stderr,"Usage: %s destinataire\n", argv[0]);
        exit(EXIT_FAILURE);
    };
    envoyer_mail(argv[0]);
    exit(EXIT_FAILURE);
}

void envoyer_mail(const char *mail_destinataire)
{
    // ouverture du stream d'envoi
    char commande_envoi_mail[TAILLE_MAX_COMMANDE];
    snprintf(commande_envoi_mail, TAILLE_MAX_COMMANDE,
             "sendmail %s", mail_destinataire);
    FILE *stream_envoi_mail = popen(commande_envoi_mail, "w");
    assert(stream_envoi_mail != NULL);

    fabriquer_message_liste_fichiers(stream_envoi_mail);
    pclose(stream_envoi_mail);
}

void fabriquer_message_liste_fichiers(FILE *sortie)
{
    // envoi du message
    fprintf(sortie, "Subject: ls -l\n\n"
            "Cher ami,\n"
            "voici mon répertoire:\n");

    FILE *stream_liste_fichiers = popen("ls -l","r");
    assert(stream_liste_fichiers != NULL);

    int c;
    while( (c = fgetc(stream_liste_fichiers)) != EOF) {
        fputc(c, sortie);
    }
    pclose(stream_liste_fichiers);

    fprintf(sortie, "---\nLe Robot\n");
}
