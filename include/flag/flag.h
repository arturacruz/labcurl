#ifndef FLAG_H
#define FLAG_H

#include "../string/string.h"
#include <stdbool.h>
#include "../file.h"

typedef struct {
    string* flag;
    string* content;
} flag_t;

flag_t* flag_new(char* flag, char* content);
bool is_flag(char* flag);
void flag_destroy(flag_t** flag);

file_t* flag_f(flag_t *curr);
int flag_n(flag_t* curr);

#endif // !FLAG_H
