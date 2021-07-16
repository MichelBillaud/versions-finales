#include <stdio.h>
#include <stdlib.h>

struct Array {
     int size;
     float *data;
};

void array_init (struct Array *array_ptr, int size) 
{
	array_ptr->size = size;
	array_ptr->data = malloc(size * sizeof(float));
}

void array_set(struct Array *array_ptr, int index, float new_value)
{
	array_ptr->data[index] = new_value;
}

float array_get(struct Array *array_ptr, int index)
{
	return array_ptr->data[index];
}

int array_size(struct Array *array_ptr)
{
	return array_ptr->size;
}

void array_free(struct Array *array_ptr) 
{	
	free(array_ptr->data);
    array_ptr->data = NULL;    // précaution contre double array_free
	array_ptr->size = 0;
}

void array_resize(struct Array *array_ptr, int new_size)
{
	array_ptr->data = realloc(array_ptr->data, 
	                          new_size * sizeof(float));
	array_ptr->size = new_size;
}
	
void test()
{
	struct Array a;
	printf("quelle taille ? ");
	int taille;
	scanf("%d", &taille);
	
	array_init(&a, taille);

	// test nombre éléments
	printf("le tableau contient %d flottants\n", array_size(&a));

	// écriture (de 100 en 100);
	for (int i = 0; i < array_size(&a); i++) {
		array_set(&a, i,  100*i);
	}

	// consultation
	for (int i = 0; i < array_size(&a); i++) {
		printf("%d -> %f\n", i, array_get(&a, i));
	}

	// libération
	array_free(&a);
}

int main()
{
	test();
	return 0;
}

