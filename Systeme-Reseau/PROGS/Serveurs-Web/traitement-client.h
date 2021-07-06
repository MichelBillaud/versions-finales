/*
  Serveurs-web/traitement-client.h

  projet serveur WEB
  Communication avec un client
 */

#ifndef TRAITEMENT_CLIENT_H
#define TRAITEMENT_CLIENT_H

void servir_client(int fd_client, const char *repertoire);
void retourner_document(FILE *out,
                        const char *nom_document,
                        const char *repertoire);

void repondre_erreur_404 (FILE *out, const char *nom_document);
void repondre_erreur_400(FILE *out);

#endif
