#ifndef VEC_STR_H
#define VEC_STR_H

#include "string/string.h"

typedef enum {
    STR, FLAG,
} vec_type;

typedef struct {
    void** data;
    vec_type type;
    int size;
    int capacity;
} vec_t;

vec_t* vec_new(vec_type type);
void* vec_get(vec_t* vec, int idx);
int vec_size(vec_t* vec);
void vec_add(vec_t* vec, void* obj);
void vec_destroy(vec_t** vec);

#endif // !VEC_STR_H
