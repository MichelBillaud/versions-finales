/*
 * automate
 *
 * exemple de codage d'automate,
 * reconnait les mots qui
 * ont un nombre pair de lettres
 * et au moins un chiffre
 * Les autres caractères sont ignorés
 */
#include <iostream>
#include <cassert>

using namespace std;


enum Etat {   Lp0c, Li0c, Lp1c, Li1c };
enum Categorie { Lettre, Chiffre, Autre };


const Etat etatInitial = Lp0c;
const Etat etatFinal   = Lp1c;

Etat delta[][3] =
{
    { Li0c, Lp1c, Lp0c },
    { Lp0c, Li1c, Li0c },
    { Li1c, Lp1c, Lp1c },
    { Lp1c, Li1c, Li1c },
};

Categorie categorie(char x)
{
    return isdigit(x) ? Chiffre
           : isalpha(x) ? Lettre
           : Autre;
}

bool estValide (const char chaine[])
{
    Etat etat = etatInitial;
    for (int i=0; chaine[i] != '\0'; i++)
    {
        Categorie x = categorie(chaine[i]);
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
    assert ( estValide("5"));
    assert ( estValide("a1bcd"));
    assert ( ! estValide("aa"));
    assert ( ! estValide("z9"));
    assert ( estValide("ab3"));
    assert ( estValide("a3b"));
    assert ( estValide("a1b2"));
    assert ( estValide("314pi"));
    cout << "-- tests ok" << endl;
}
