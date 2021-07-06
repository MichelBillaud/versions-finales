/*
  Serveurs-Web/traitement-client.c

  projet serveur WEB
  Communication avec un client
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include "constantes.h"
#include "traitement-client.h"

void afficher_entete(FILE* in)
{
    char *ligne = NULL;
    size_t taille_ligne = 0L;
    while (true) {
        ssize_t n = getline(& ligne, &taille_ligne, in);
        printf("-- %s", ligne);
        if (n <= 2) break;
    }    
    free(ligne);
}

void servir_client(int fd_client, const char *racine_documents)
{
    FILE *in = fdopen(fd_client, "r");
    // si on attache deux FILEs au même descripteur,
    // la fermeture de l'un entraine la fermeture de l'autre.
    // Ici on veutDonc on duplique.
    FILE *out = fdopen(dup(fd_client), "w");

    /* lecture de la première ligne de requête, 
     * du genre "GET quelquechose ..." */
    char *ligne = NULL;
    size_t taille_ligne = 0L;
    getline(& ligne, &taille_ligne, in); 
    printf("> %s\n", ligne);
    afficher_entete(in);
    char verbe[100], nom_document[100];
    sscanf(ligne,"%100s %100s", verbe, nom_document);
    free(ligne);
   

    if (strcmp(verbe, "GET") == 0) {
        retourner_document(out, nom_document, racine_documents);
    } else {
        repondre_erreur_400(out);
    } 

    fflush(out);    
    fclose(in);
    fclose(out);
}

void transcoder_contenu_fichier(FILE *out, FILE *fichier)
{
    while (true) {
        int c = fgetc(fichier);
        if (c == EOF || c < 0) break;
        switch (c) {
        case '<':
            fputs("&lt;", out);
            break;
        case '>':
            fputs("&gt;", out);
            break;
        case '&':
            fputs("&amp;", out);
            break;
        case '\n':
            fputs(CRLF, out);
            break;
        default:
            fputc(c, out);
        };
    }
    /* balises de fin */
    fputs("</listing></table></center></body></html>"
          CRLF, out);
}

void retourner_document(FILE *out,
                        const char *nom_document,
                        const char *racine_documents)
{
    char nom_fichier[200];
    snprintf(nom_fichier, 200,
             "%s%s", racine_documents, nom_document);

    if (strstr(nom_fichier, "/../") != NULL) {
        /* tentative d'accès hors du répertoire ! */
        repondre_erreur_404(out, nom_document);
        return;
    };
    FILE * fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        repondre_erreur_404(out, nom_document);
        return;
    };

    fprintf(out,
            "HTTP/1.1 200 OK" CRLF
            "Server: " VERSION CRLF
            "Content-Type: text/html; " CHARSET CRLF
            CRLF);

    fprintf(out,
            "<!doctype html>" CRLF
            "<html><head>" CRLF
            "<meta charset=\"" CHARSET "\">" CRLF
            "<title>Fichier %s</title></head>" CRLF
            "<body bgcolor=\"white\">"
            "<h1>Fichier %s</h1>" CRLF
            "<center><table>"
            "<tr><td bgcolor=\"yellow\"></td></tr>"
            "<listing>" CRLF,
            nom_document, nom_fichier);

    transcoder_contenu_fichier(out, fichier);
}

void repondre_erreur_404(FILE *out, const char *nom_document)
{
    /* envoi de la réponse : entête */
    fprintf(out,
            "HTTP/1.1 404 Not Found" CRLF
            "Server: " VERSION CRLF
            "Content-Type: text/html; charset=" CHARSET CRLF
            CRLF);

    /* corps de la réponse */
    fprintf(out,
            "<!doctype HTML>" CRLF
            "<HTML><HEAD>" CRLF
            "<meta charset=\"" CHARSET "\">" CRLF
            "<TITLE>404 Not Found</TITLE>" CRLF
            "</HEAD><BODY BGCOLOR=\"yellow\">" CRLF
            "<H1>Pas trouvé !</H1>" CRLF
            "Le document <font color=\"red\"><tt>%s</tt></font> "
            "demandé<br>n'est pas disponible.<P>" CRLF
            "<hr> Le webmaster"
            "</BODY></HTML>" CRLF,
            nom_document);
    fflush(out);
}

void repondre_erreur_400(FILE *out)
{
    fprintf(out,
            "<!doctype html>" CRLF
            "<HTML><HEAD>" CRLF
            "<meta charset=\"" CHARSET "\">" CRLF
            "<TITLE>400 Bad Request</TITLE>" CRLF
            "</HEAD><BODY BGCOLOR=\"yellow\">" CRLF
            "<H1>Bad Request</H1>"
            "Vous avez envoyé une requête que "
            "ce serveur ne comprend pas." CRLF
            "<hr>Le webmaster"
            "</BODY></HTML>" CRLF);
}
