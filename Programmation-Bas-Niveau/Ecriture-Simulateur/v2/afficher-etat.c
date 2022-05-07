
void afficher_etat(struct Machine *m)
{
     /* en-tête du tableau  */
     printf("ADR ");
     for (int colonne = 0; colonne<16; colonne++)
          printf("    %x", colonne);
     printf("\n   +");
     for (int colonne = 0; colonne<16; colonne++)
          printf("-----");
     printf("\n");

     /* vue de la mémoire sous forme de
        16 lignes de 16 nombres de 4 chiffres hexa,
        précédées par l'adresse en hexa */

     for (int ligne = 0; ligne < 16; ligne ++) {
          int adresse = 16*ligne;
          printf("%02x | ", adresse);
          for (int colonne = 0; colonne < 16; colonne ++) {
               printf("%04x ", m -> M[ adresse + colonne ]);
          }
          printf("\n");
     }
     /* les registres */
     printf("Registres:  ACC [hex=%04x dec=%6d]  PC [%04x]  HALT [%x]\n" ,
            m -> ACC, m->ACC, m-> PC, m->HALT );
}
