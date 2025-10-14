#include "../../include/string/string.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

string* string_new(char* str)
{
    string* s = malloc(sizeof(string));
    
    int len = strlen(str);

    char* data = malloc(sizeof(char) * (len + 1));

    strcpy(data, str);
    s->str = data;
    s->len = len;
    return s;
}

string* string_from(char* str, int len)
{
    string* s = malloc(sizeof(string));

    char* data = malloc(sizeof(char) * (len + 1));

    strcpy(data, str);
    s->str = data;
    s->len = len;
    return s;
}

string* string_copy(string* s)
{
    return string_from(s->str, s->len);
}

string* string_alloc(int len) 
{
    string* s = malloc(sizeof(string));
    char* data = malloc(sizeof(char) * (len + 1));

    s->str = data;
    s->len = len;
    return s;
}

string* string_concat(string** s1p, string** s2p)
{
    string* s1 = *s1p;
    string* s2 = *s2p;
    int new_len = s1->len + s2->len;

    string* new_str = string_alloc(new_len);

    for(int i = 0; i < s1->len; i++) 
    {
        new_str->str[i] = s1->str[i]; 
    }
    for(int i = 0; i <= s2->len; i++) 
    {
        new_str->str[i + s1->len] = s2->str[i]; 
    }

    string_destroy(s1p);
    string_destroy(s2p);
    return new_str;
}

bool string_compare(string* s1, string *s2)
{ 
    for(int i = 0; true; i++)
    {
        char s1c = s1->str[i];
        char s2c = s2->str[i];

        if(s1c == '\0' && s2c == '\0')
            return true;

        if(s1c != s2c)
            return false;
    }
    return true;
}

bool string_compare_str(string* s1, char *s2)
{
    for(int i = 0; true; i++)
    {
        char s1c = s1->str[i];
        char s2c = s2[i];

        if(s1c == '\0' && s2c == '\0')
            return true;

        if(s1c != s2c)
            return false;
    }
    return true;
}

void string_replace(string** s, char* ocurr, char with)
{
    string* sp = *s;
    for(int i = 0; i < sp->len; i++)
    {
        for(int j = 0; ocurr[j] != '\0'; j++) 
        {
            if(sp->str[i] == ocurr[j]) 
            {
                sp->str[i] = with;
            }
        }
    }
}

void string_destroy(string **s)
{
    free((*s)->str);
    free(*s);
}
