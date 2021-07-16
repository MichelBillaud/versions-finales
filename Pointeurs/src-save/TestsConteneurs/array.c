
#include "array.h"
#include <stdlib.h>

#define ARRAY_MIN_CAPACITY 4

struct Array* array_new()
{
    struct Array *ptr = malloc(sizeof (void *));
    array_initialize(ptr);
    return ptr;
}

void array_delete(struct Array *this) {
    array_clear(this);
    free(this);
}

void array_clear(struct Array *this) 
{
    free(this->elements);
    array_initialize(this);
}

void array_initialize(struct Array *this)
{
    this->nb_elements = 0;
    this->capacity = 0;
    this->elements = NULL;
}

size_t array_size(struct Array *this) 
{
    return this->nb_elements;
}

void** array_addr_of(struct Array *this, int index)
{
    return this->elements + index;
}

void array_set(struct Array *this, int index, void *element)
{
    * array_addr_of(this, index) = element;
}

void * array_get(struct Array *this, int index)
{
    return * array_addr_of(this, index);
}

void array_add(struct Array *this, void * element)
{
    // allocate more room if needed
    if (this->nb_elements == this->capacity) {
        this->capacity = (this->capacity == 0)
                ? ARRAY_MIN_CAPACITY
                : 2 * this->capacity;
        this->elements = realloc(this->elements, this->capacity * sizeof(void *));
    }
    // append element
    this->elements[this->nb_elements ++] = element;
}