#include "../include/vec.h"
#include "../include/string/string.h"
#include "../include/flag.h"
#include <stdlib.h>

void vec_expand(vec_t* vec)
{
    int old_capacity = vec->capacity;
    vec->capacity *= 2;
    void** new_data = malloc(8 * vec->capacity);

    for(int i = 0; i < old_capacity; i++)
    {
       new_data[i] = vec->data[i]; 
    }
    free(vec->data);
    vec->data = new_data;
}

vec_t* vec_new(vec_type type)
{
    vec_t* vec = malloc(sizeof(vec_t));
    vec->type = type;
    vec->capacity = 8;
    vec->size = 0;

    vec->data = malloc(8 * vec->capacity);
    return vec;
}

int vec_size(vec_t* vec)
{
    return vec->size;
}

void* vec_get(vec_t* vec, int idx)
{
    if(idx > vec->size)
    {
        return NULL;
    }
    return vec->data[idx];
}

void vec_add(vec_t* vec, void* obj)
{
    if(vec->size == vec->capacity)
    {
        vec_expand(vec);
    }
    vec->data[vec->size] = obj;
    vec->size++;
}

void vec_destroy(vec_t** vec)
{
    vec_t* vecp = *vec;
    for(int i = 0; i < vecp->size; i++)
    {
        void* obj = vecp->data[i];
        switch(vecp->type)
        {
            case STR:
                string_destroy((string**) &obj);
                break;
            case FLAG:
                flag_destroy((flag_t**) &obj);
                break;
        }
    }
    free(vecp->data);
    free(*vec);
}


