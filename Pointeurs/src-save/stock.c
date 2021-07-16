#include <stdio.h>

#include <string.h>
#include <stdbool.h>

#define TAILLE_MAX_STOCK 100
#define LONGUEUR_MAX_DESCRIPTION 50

struct Article {
	int reference;
	char description[LONGUEUR_MAX_DESCRIPTION];
	int  quantite;
};

struct Stock {
	int nombre_articles;
	struct Article articles[TAILLE_MAX_STOCK];
};


void initialiser_stock(struct Stock *adr_stock)
{
	adr_stock->nombre_articles = 0;
}

bool stock_est_plein(struct Stock *adr_stock)
{
	return adr_stock->nombre_articles == TAILLE_MAX_STOCK;
}

/**
 * cherche dans un stock un article à partir de sa référence.
 * retourne un pointeur sur l'article si présent, NULL sinon.
 */
struct Article *chercher_par_reference(struct Stock *adr_stock, 
                                       int reference)
{
	for (int i = 0; i < adr_stock->nombre_articles; i++) {
		if (adr_stock->articles[i].reference == reference) {
			return adr_stock->articles + i;              // trouvé
		}
	}
	return NULL;                                         // pas trouvé 
}

/**
 * ajoute un article dans le stock.
 * on transmet l'adresse pour éviter de faire une copie
 * 
 * PRECAUTIONS, il est de la responsabilité de l'utilisateur de la 
 * fonction de vérifier
 * - que le stock n'est pas plein.
 * - que la référence n'est pas déjà présente.
 * - que la description n'est pas trop longue
 */
 
void ajouter_article(struct Stock *adr_stock,
                     struct Article *adr_article)
{
	adr_stock->articles[adr_stock->nombre_articles++] = *adr_article;
}

// dans les actions, passage d'adresse 
// 1. pour éviter de faire une copie, 
// 2. et pour qu'une action puisse modifier un article

typedef void (*ActionSurArticle)(struct Article *);

void pour_tout_article(struct Stock *stock, ActionSurArticle action)
{
	for (int i = 0; i < stock->nombre_articles; i++) {
		printf("%3d ", i);
		action(stock->articles + i);               // c'est une adresse
	}
}

void action_afficher_article(struct Article *adr_article)
{
	printf("%06d %6d %s\n", adr_article->reference,
	                        adr_article->quantite,
	                        adr_article->description);						 
}


void test_recherche(struct Stock *adr_stock, int reference)
{
	printf("- Recherche de la réference %d\n", reference);
	
	struct Article *adr_article
					= chercher_par_reference(adr_stock, reference);
	if (adr_article == NULL) {
		printf("absente\n");
	} else {
		action_afficher_article(adr_article);
	}
}

void test_1 ()
{
	struct Stock stock;
	struct Article article_patates = { 
		.reference = 123,
		.quantite = 20,     
		.description = "Sac 3kg de patates"
	};
	// initialisation de structure style C99, voir
	// http://en.cppreference.com/w/c/language/struct_initialization
	
	struct Article article_chaussettes = {
		.reference = 234,
		.description = "Paire de chaussettes vertes",
		.quantite = 12
	};
	
	struct Article article_logiciel = {
		.reference = 89,
		.description = "Compilateur C ANSI en solde",
		.quantite  = 5
	};
	
	printf("* Initialisation et ajouts\n");

	initialiser_stock(& stock);
	ajouter_article(& stock, &article_patates);
	ajouter_article(& stock, &article_chaussettes);
	ajouter_article(& stock, &article_logiciel);
	
	printf("* Parcours\n");
	
	pour_tout_article(& stock, action_afficher_article);

	printf("* Tests de recherche\n");
	
	test_recherche(& stock, 234);
	test_recherche(& stock, 999);
	}

int main()
{
	test_1();
	return 0;
}
