#include <stdlib.h>
#include <stdbool.h>

#include <stdio.h>
#include <ctype.h>
/* 
	Le simulateur possède une mémoire
	de 1ko
*/
#define TAILLE_MEMOIRE 1024
unsigned char memoire[TAILLE_MEMOIRE];

void afficherMemoire (int nbOctets)
{
	int a, i;
	printf("Contenu de la mémoire (%d premiers octets) :\n", nbOctets);
	for (a = 0; a < nbOctets; a += 16) {
		printf("%04x :", a);
		for (i = 0; i < 16; i++) {
			printf(" %02x", memoire[a+i]);
		}
		printf("\n");
	}
}

int hex2int(char caractere) {
	return caractere + (isdigit(caractere) ?  0 - '0' // 0-9
		                : caractere <= 'F' ? 10 - 'A' // A-F
	                    :                    10 - 'a'); // a-f
}


void chargerExecutable (FILE * executable)
{
	int ligne = 1, position = 0;  // position dans le source
	int caractere;
	
	bool premier = true;  // premier quartet de l'octet ?
	int quartet;

	int adresse = 0;  // adr. mÃ©moire Ã  remplir   
	
	while ( (caractere = fgetc(executable)) != EOF ) {
		position ++;
		if (caractere == '\n') {
			ligne ++;
			position = 0;
			quartet = 0;
			continue;
		}
		if (isspace(caractere)) { // ignorÃ©
			continue;
		}
		if (isxdigit(caractere)) {
			if (premier) {
				quartet = hex2int(caractere);
			} else {
				memoire[adresse++] = (quartet << 4) | hex2int(caractere);
			}
			premier = ! premier;
			continue;
		} 
		fprintf(stderr,"%d: caractère %c inattendu position %d\n",
						ligne, caractere, position);
	}
}

int main(int argc, char * argv[]) 
{
	FILE * executable;
	if (argc != 2) {
		fprintf(stderr, "usage %s exécutable\n", argv[0]);
		return EXIT_FAILURE;
	}
	executable = fopen(argv[1], "r");
	if (executable == NULL) {
		perror("ouverture fichier exécutable");
		return EXIT_FAILURE;
	}
	chargerExecutable(executable);
	afficherMemoire(128);
	
	return EXIT_SUCCESS;
}
