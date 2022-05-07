char * mnemoniques[] = {
     "loadi",     "load",      "loadx",
     "store",     "storex",
     "add",       "sub",
     "jmp",       "jneg",      "jzero",
     "jmpx",      "call",      "halt",
     "illegal13", "illegal14", "illegal15"
};


bool valider_adresse(struct Machine *m,
                    unsigned int adresse, char message[])
{
     if (adresse < 256)
          return true;
     else {
          printf("-- PC=%x * ERREUR ACCES MEMOIRE ADRESSE =%x --%s\n",
                 m->PC, adresse, message);
          printf("-- Machine arretee.\n");
          m->HALT=true;
          return false;
     }
}

void lancer_execution(struct Machine * m)
{
     m->ACC  = 0;
     m->HALT = false;
     m->PC   = 0;

     /* ready to go ! */

     while ( ! m->HALT ) {
          if (! valider_adresse(m, m->PC, "lecture instruction"))
               break;

          uint16_t mot = m -> M[ m -> PC ];
          unsigned int code     =  (mot >> 12);
          unsigned int operande =  (mot & 0xfff);

          printf("- pc=%d execution de %s %d\n",
                 m->PC, mnemoniques[code], operande);

          switch (code) {
          case 0 :  /* loadi */
	       /* extension du signe de l'opérande 12->16 bits */
               m->ACC = ((int16_t)(operande << 4))  >> 4;
               m->PC ++;
               break;
          case 1 :  /* load */
               if (valider_adresse(m, operande, "operande load")) {
                    m->ACC = (int16_t)(m->M [operande]);
                    m->PC ++;
               }
               break;
          case 5 :  /* add */
               if (valider_adresse(m, operande, "operande add")) {
                    m->ACC += (int16_t)(m->M [operande]);
                    m->PC ++;
               }
               break;
          case 3 :  /* store */
               if (valider_adresse(m, operande, "operande store")) {
                    m->M [operande] = (int16_t) m->ACC;
                    m->PC ++;
               }
               break;
          case 0xC : /* halt */
               m->HALT = true;
               break;
          default:
               printf("ERREUR : operation illegale '%x'\n", code);
               break;
          }
          printf("  ACC=%d\n", m->ACC);
     }
}
