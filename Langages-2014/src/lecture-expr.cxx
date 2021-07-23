// à compiler avec  C++ version 11
//      g++ -std=c++11 lecture-expr.cxx -o lecture-expr

#include <iostream>
using namespace std;

// --------------------------------------

enum TypeLexeme {
    OUVRANTE, FERMANTE, 	PLUS, MOINS, ETOILE, BARRE,
    NOMBRE, IDENTIFICATEUR,     FIN, ERREUR
};

// --------------------------------------

class AnalyseurLexical {
private:
    string m_chaine;
    uint   m_longueur, m_position;
    TypeLexeme m_typeLexeme;
    string m_lexeme;

public:

    AnalyseurLexical(const string & chaine) :
        m_chaine(chaine),
        m_longueur(chaine.size()),
        m_position(0)
    {
        avancer();
    }

    void avancer()
    {
        m_lexeme = "";
        while ((m_position < m_longueur) &&
                isspace(m_chaine[m_position])) {
            m_position++;
        }
        if (m_position == m_longueur) {
            m_typeLexeme = FIN;
            return;
        }
        char premier = m_chaine[m_position++];
        m_lexeme = premier;
        // nombres
        if (isdigit(premier)) {
            m_typeLexeme = NOMBRE;
            while ((m_position < m_longueur) &&
                    isdigit(m_chaine[m_position])) {
                m_lexeme += m_chaine[m_position++];
            }
            return;
        }
        // identificateurs
        if (isalpha(premier)) {
            m_typeLexeme = IDENTIFICATEUR;
            while ((m_position < m_longueur) &&
                    isalnum(m_chaine[m_position])) {
                m_lexeme += m_chaine[m_position++];
            }
            return;
        }
        // symboles
        m_typeLexeme
        = premier == '(' ? OUVRANTE
          : premier ==  ')' ? FERMANTE
          : premier == '+' ? PLUS
          : premier == '-' ? MOINS
          : premier == '*' ? ETOILE
          : premier == '/' ? BARRE
          : ERREUR;
    }

    TypeLexeme typeLexeme(void) const
    {
        return m_typeLexeme;
    }
    string lexeme(void) const
    {
        return m_lexeme;
    }
};

void test_analyse_lexicale(const string & s)
{
    cout << "-- test analyse lexicale" << endl;
    cout << "chaine : " << s << endl;
    AnalyseurLexical lex(s);
    while (lex.typeLexeme() != FIN) {
        cout << "- " << lex.typeLexeme()
             << " " << lex.lexeme() << endl;
        lex.avancer();
    };
}

// ------------------------------------------------------

class Expression {
public:
    virtual ~Expression()   {} ;
    virtual void afficher() const = 0;
};

class ExpressionBinaire
    : public Expression
{
    string m_nom;
    const Expression * m_gauche, *m_droite;

public:
    ExpressionBinaire(const string  & nom,
                      const Expression * gauche,
                      const Expression * droite)
        : 	m_nom(nom),
            m_gauche(gauche),
            m_droite(droite)
    {};

    void afficher() const override
    {
        cout << "(  "<< m_nom << " de ";
        m_gauche->afficher();
        cout << " et de ";
        m_droite->afficher();
        cout << ") ";
    }

    ~ExpressionBinaire() {
        delete m_gauche;
        delete m_droite;
    }
};

class ExpressionSimple
    : public Expression
{
    string m_type, m_nom;
public:
    ExpressionSimple(const string & type, const string & nom)
        : m_type(type), m_nom(nom)
    {}
    void afficher() const override
    {
        cout << "la " << m_type << " " << m_nom;
    }
};

// ---------------------------------------------------------------
class AnalyseurSyntaxique
{
    AnalyseurLexical m_lex;
    Expression *m_expr = NULL;
public:
    AnalyseurSyntaxique(const string & chaine)
        : m_lex(chaine)
    {}

    Expression * expression() {
        if (m_expr == NULL) {
            m_expr = lireExpr();
        }
        return m_expr;
    }

    Expression * lireExpr()
    {
        Expression * expr = lireTerme();
        for(;;) {
            TypeLexeme t = m_lex.typeLexeme();
            if (t == PLUS) {
                m_lex.avancer();
                Expression * terme = lireTerme();
                expr = new ExpressionBinaire("la somme ",
                                             expr, terme);
            } else if (t == MOINS) {
                m_lex.avancer();
                Expression * terme = lireTerme();
                expr = new ExpressionBinaire("la difference ",
                                             expr, terme);
            } else {
                break;
            }
        }
        return expr;
    }

    Expression * lireTerme() 	{
        Expression * terme = lireFacteur();
        for(;;) {
            TypeLexeme t = m_lex.typeLexeme();
            if (t == ETOILE) {
                m_lex.avancer();
                Expression * facteur = lireFacteur();
                terme = new ExpressionBinaire("le produit ",
                                              terme, facteur);
            } else if (t == BARRE) {
                m_lex.avancer();
                Expression * facteur = lireFacteur();
                terme = new ExpressionBinaire("le quotient ",
                                              terme, facteur);
            } else {
                break;
            }
        }
        return terme;
    }

    Expression * lireFacteur()
    {
        Expression *facteur = NULL;
        if (m_lex.typeLexeme() == OUVRANTE) {
            m_lex.avancer();
            facteur = lireExpr();
            if (m_lex.typeLexeme() != FERMANTE) {
                cout << "** oups il manque une fermante" << endl;
            }
        } else if (m_lex.typeLexeme() == NOMBRE) {
            facteur = new ExpressionSimple("constante ",
                                           m_lex.lexeme());
        } else if (m_lex.typeLexeme() == IDENTIFICATEUR) {
            facteur = new ExpressionSimple("variable ",
                                           m_lex.lexeme());
        }
        else {
            cout << "** oups, probleme avec "
                 << m_lex.lexeme() << endl;
        }
        m_lex.avancer();
        return facteur;
    }
};

void test_analyse_syntaxique(const string & s)
{
    cout << "-- test analyse  syntaxique" << endl;
    cout << "chaine : " << s << endl;
    AnalyseurSyntaxique a(s);
    Expression * r = a.expression();
    r->afficher();
    cout << endl;
    delete r;
}

// -----------------------------------------------------

int main(int argc, char **argv)
{
    test_analyse_lexicale("beta * beta - (4*  alpha*gamma)");
    test_analyse_syntaxique("beta * beta - (4*  alpha*gamma)");
    test_analyse_syntaxique( "HT * (100+TVA)/100");
    return 0;
}
