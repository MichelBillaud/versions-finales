/* 
 * File:   array.h
 * Author: billaud
 *
 * Created on 15 avril 2019, 18:53
 */

#ifndef ARRAY_H
#define ARRAY_H

#include "stdlib.h"

struct Array {
    size_t nb_elements;
    size_t capacity;
    void ** elements;
};

struct Array* array_new();
void   array_delete    (struct Array *this);
void   array_clear     (struct Array *this);
void   array_initialize(struct Array *this);
void   array_add       (struct Array *this, void * element);
size_t array_size      (struct Array *this);

void** array_addr_of   (struct Array *this, int index);
void   array_set       (struct Array *this, int index, void *element);
void*  array_get       (struct Array *this, int index);



#endif /* ARRAY_H */

