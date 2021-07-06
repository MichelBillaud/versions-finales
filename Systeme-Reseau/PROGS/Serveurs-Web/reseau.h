// serveurs Web,  reseau.h

#ifndef RESEAU_H
#define RESEAU_H

int ouvrir_serveur_tcp (const char port[]);
int ouvrir_client(int fd_serveur);

#endif
