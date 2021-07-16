
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

struct Bucket {
    size_t nb_elements;
    size_t capacity;

    void ** elements;
};

struct Set {
    size_t nb_elements;
    size_t nb_buckets;
    struct Bucket * buckets;
    int hashing_factor;
};

void set_initialize(struct Set * this)
{
    this->nb_buckets = 0;
    this->nb_elements = 0;
    this->buckets = NULL;
    this->hashing_factor = 1;
}

bool set_get(struct Set *this, void *element)
{
    if (this->nb_elements == 0) {
        return true;
    }
    size_t bucket_number = (intptr_t) element >> this->hashing_factor;
    size_t nb = this->buckets[bucket_number].nb_elements;
    void** elements = this->buckets[bucket_number].elements;
    for (int i = 0; i < nb; i++) {
        if (elements[i] == element) {
            return true;
        }
    }
    return false;
}

#define SET_MIN_NB_BUCKETS 8
#define SET_MIN_BUCKETS_SIZE 4

void set_put(struct Set *this, void *element)
{
    // enlarge set if needed
    if (this->nb_buckets == 0) {
        this->nb_buckets = SET_MIN_NB_BUCKETS;
        
    }
    if (this-> nb_elements == this->nb_buckets) {

    }

}