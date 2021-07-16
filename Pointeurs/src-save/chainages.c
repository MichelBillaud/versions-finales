#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Element {
	int value;
	struct Element *next_ptr;
};

struct Stack {
	struct Element *top_ptr;
};

void stack_init (struct Stack *stack_ptr) 
{
	stack_ptr->top_ptr = NULL;
}

void stack_push (struct Stack *stack_ptr, int value)
{
	struct Element *new = malloc(sizeof(struct Element));
	new->value    = value;
	new->next_ptr = stack_ptr->top_ptr;
	stack_ptr->top_ptr = new;
};

bool stack_is_empty (struct Stack *stack_ptr)
{
	return stack_ptr->top_ptr == NULL;
}

int stack_top (struct Stack *stack_ptr) 
{
	// attention la pile ne doit pas être vide
	return stack_ptr->top_ptr->value;
}

void stack_pop (struct Stack *stack_ptr)
{
	if (stack_is_empty (stack_ptr)) {
		return;
	}
	struct Element *old = stack_ptr->top_ptr;
	stack_ptr->top_ptr = old->next_ptr;
	free (old);
}

void stack_free (struct Stack *stack_ptr)
{
	while ( ! stack_is_empty(stack_ptr)) {
		stack_pop(stack_ptr);
	}
}	

void test()
{
	struct Stack s;
	stack_init(& s);
	
	// empiler 10,20,30,40,50
	for (int i = 1; i <= 5; i++) {
		stack_push (&s, 10 * i);
		printf("%p\n", s.top_ptr);
	}
	// afficher en dépilant, devrait fournir 50 40 ...
	while( ! stack_is_empty (&s)) {
		printf("%d ", stack_top(&s));
		stack_pop(&s);
	};
	printf("\n");
	
	stack_free(&s);
}	

int main()
{
	printf("%zu\n", sizeof(struct Element));
	test();
	return 0;
}

