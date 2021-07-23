/**
 * reconnaissance d'un motif avec jokers
 * version itérative
 */

#include <stack>

bool reconnait(const char * motif, 
               const char * chaine) 
{
  stack <pair <const char *, const char * > > 
          alternatives;
  const char *m = motif,  *c = chaine;
  pair<const char *, const char *> p(m,c);
  alternatives.push(p);

  while (! alternatives.empty()) 
  {
    m = alternatives.top().first;
    c = alternatives.top().second;
    alternatives.pop();
    
    // le motif est examiné lettre par lettre
    for ( ; *m; m++) 
    {
      if (*m == '*') {
        if (*c != '\0') {
          // noter alternative : l'étoile absorbe 
          // au moins un caractère de la chaine
          p.first  = m;
          p.second = c+1;
          alternatives.push(p);
        };
      } else if (*c == '\0') { // fin de chaine
            break; 
      } else if (*m == '?' || *m == *c) {
          c++;
      } else {                // mauvais caractère
          break;
      };
     }
    // arrivé au bout ?
    if (*m == '\0' && *c == '\0') {
       return true;
    }
  }
  // plus d'alternatives ?
  return false;
}
