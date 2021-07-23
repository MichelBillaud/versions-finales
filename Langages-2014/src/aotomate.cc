/*
 * automate
 * 
 * exemple de codage d'automate,
 * reconnait les mots sur {a,b} qui 
 * ont un nombre pair de a et 
 * au moins un b.
 * Les autres caractères sont ignorés
 */
#include <iostream>
#include <cassert>

using namespace std;


enum Etat {
  ApairsSansB,   
  AimpairsSansB,
  ApairsAvecB,   
  AimpairsAvecB, 
};

const Etat etatInitial = ApairsSansB;
const Etat etatFinal   = ApairsAvecB;

Etat delta[][3] = 
{
  { AimpairsSansB, ApairsAvecB, ApairsSansB},
  { ApairsSansB, AimpairsAvecB, AimpairsSansB},
  { AimpairsAvecB, ApairsAvecB, ApairsAvecB},
  { ApairsAvecB, AimpairsAvecB, AimpairsAvecB},
};

// on suppose qu'on n'a que des a et des b 
// dans la chaine

bool estValide (const char chaine[])
{
  Etat etat = etatInitial;
  for (int i=0; chaine[i] != '\0'; i++) 
  {
    int x = (chaine[i] == 'a') ? 0 : 
            (chaine[i] == 'b') ? 1 :
                                 2;
    etat = delta[etat][x];   // transition
  }
  return (etat == etatFinal);
}

// ----------------------------------------------
int main(int argc, char **argv)
{
  cout << "-- debut tests" << endl;
	assert ( ! estValide(""));
	assert ( ! estValide("a"));
	assert ( estValide("b"));
  assert ( estValide("xxxbyyy"));
	assert ( ! estValide("aa"));
	assert ( ! estValide("ab"));
	assert ( estValide("aab"));
	assert ( estValide("aba"));
	assert ( estValide("baba"));
	assert ( estValide("baaaaaba"));
	assert ( estValide("bacdefaaaaba"));
  cout << "-- tests ok" << endl;
}  
