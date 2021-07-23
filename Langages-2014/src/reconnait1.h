/**
 * reconnaissance d'un motif avec jokers
 * version r�cursive
 */

bool reconnait(const char * motif, 
              const char * chaine) 
{
  if (*motif == '\0') {
    return *chaine == '\0';
  }
  // ? : on saute un caract�re
  if (*motif == '?') {
    return (*chaine != '\0') 
          && reconnait(motif+1, chaine+1);
  }
  // * : on saute l'�toile ou un caract�re
  if (*motif == '*') {
    return reconnait(motif+1, chaine)
        || ((*chaine != '\0') 
            && reconnait(motif, chaine+1));
  }
  // autres caract�res
  return (*motif == *chaine) 
          && reconnait(motif+1, chaine+1);    
}
