#ifndef STRING_H
#define STRING_H

#include <stdbool.h>

typedef struct {
    char* str;
    int len;
} string;

string* string_new(char* str);
string* string_from(char* str, int len);
string* string_alloc(int len);
string* string_copy(string* s);
string* string_concat(string** s1, string** s2);
void string_replace(string** s, char* ocurr, char with);
void string_destroy(string** str);

#endif 
