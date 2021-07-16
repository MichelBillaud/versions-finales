#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Element {
	int value;
	struct Element *next_ptr;
};


void afficher_tous(struct Element *first_ptr)
{
	printf("Les éléments sont :\n\t");
	for(struct Element *p = first_ptr; p != NULL; p = p->next_ptr) {
		printf(" %d", p->value);
	}
	printf("\n");
}

void afficher_plus_petits_que(struct Element *first_ptr, int value)
{
	printf("Les éléments plus petits que %d sont :\n\t", value);
	for(struct Element *p = first_ptr; p != NULL; p = p->next_ptr) {
		if (p->value >= value) {
			break;
		}
		printf(" %d", p->value);
	}
	printf("\n");
}

void afficher_immediatement_superieur(struct Element *first_ptr, int value)
{
	printf("Le premier élément >= à %d est :\n\t", value);
	for(struct Element *p = first_ptr; p != NULL; p = p->next_ptr) {
		if (p->value >= value) {
			printf(" %d", p->value);
			break;
		}
	}
	printf("\n");
}
	

void afficher_dernier_plus_petit(struct Element *first_ptr, int value)
{
	struct Element *last = NULL;
	printf("Le dernier élément < à %d est :\n\t", value);
	for(struct Element *p = first_ptr; p != NULL; p = p->next_ptr) {
		if (p->value >= value) {
			break;
		}
		last = p;
	}
	if (last != NULL) {
		printf("%d", last->value);
	}
	printf("\n");
}
	
	



int main()
{
	struct Element z = { 44, NULL};
	struct Element y = { 22, &z};
	struct Element x = { 11, &y };
	
	afficher_tous(& x);
	
	afficher_plus_petits_que(& x, 10);
	afficher_plus_petits_que(& x, 20);
	afficher_plus_petits_que(& x, 33);
	afficher_plus_petits_que(& x, 99);
	
	afficher_immediatement_superieur(& x,10);
	afficher_immediatement_superieur(& x,20);
	afficher_immediatement_superieur(& x,33);
	afficher_immediatement_superieur(& x,99);
	
	afficher_dernier_plus_petit(& x, 10);
	afficher_dernier_plus_petit(& x, 20);
	afficher_dernier_plus_petit(& x, 33);
	afficher_dernier_plus_petit(& x, 99);
	
	return 0;
}

