/*
 * motifs.cc
 * reconnaissance d'un motif avec jokers * et ?
 */

#include <iostream>
#include <cassert>

#include "reconnait1.h"

using namespace std;

int main(int argc, char **argv)
{
  cout << "-- debut tests" << endl;
	assert (  reconnait("abc", "abc"));
  assert (! reconnait("ab", "abc"));
  assert (! reconnait("abc", "ab"));
  assert (  reconnait("a?c", "abc"));
  cout << "-- tests ok" << endl;
  for(;;) {
    string motif, chaine;
    cout << "motif : ";
    getline(cin, motif);
    if (cin.fail()) break;
    cout << "chaine : ";
    getline(cin, chaine);
    if (cin.fail()) break;
    cout << "la chaine " << chaine 
         <<  (reconnait(motif.c_str(), 
                        chaine.c_str()) ? 
                 " est " : " n'est pas ")
         << "reconnue par " << motif << endl;
  }
  cout << endl << "ok." << endl;
	return 0;
}
