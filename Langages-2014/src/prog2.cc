/*
 * automate
 * 
 * exemple de codage d'automate,
 * reconnait les mots sur {a,b} qui 
 * ont un nombre pair de a et 
 * au moins un b.
 */
#include <iostream>
#include <cassert>

using namespace std;
enum Etat {
  ApairsSansB,
  AimpairsSansB
  AimpairsSansB,
  ApairsAvecB,
};

Etat delta[][2] = {
};

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
