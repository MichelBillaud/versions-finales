/**
 * reconnaissance d'un motif avec jokers
 * version récursive
 */

bool reconnait(const char * motif, 
              const char * chaine) 
{
  if (*motif == '\0') {
    return *chaine == '\0';
  }
  // ? : on saute un caractère
  if (*motif == '?') {
    return (*chaine != '\0') 
          && reconnait(motif+1, chaine+1);
  }
  // * : on saute l'étoile ou un caractère
  if (*motif == '*') {
    return reconnait(motif+1, chaine)
        || ((*chaine != '\0') 
            && reconnait(motif, chaine+1));
  }
  // autres caractères
  return (*motif == *chaine) 
          && reconnait(motif+1, chaine+1);    
}
