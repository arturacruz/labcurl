#include "../../include/string/string.h"

string* get_file_extension(string* url) 
{
    int size = 0;
    for(int i = url->len - 1; url->str[i] != '.'; i--) 
    {
        size++;
    }
    size++;

    string* ext = string_alloc(size);
    int count = ext->len;
    for(int i = url->len; count >= 0; i--) 
    {
        ext->str[count] = url->str[i];
        count--;
    }
    return ext;
}

string* get_file_start(string* url)
{
    int size = 0;
    for(int i = 0; url->str[i] != ':'; i++)
    {
        size++;
    }

    string* start = string_alloc(size);
    int count = 0;
    for(int i = 0; count < size; i++) 
    {
        start->str[count] = url->str[i];
        count++;
    }
    return start;
}

void trim_file_extension(string **filename, string* ext)
{
    string* fm = *filename;
    int new_len = fm->len - ext->len;
    string* new = string_alloc(new_len);

    for(int i = 0; i < new_len; i++)
    {
        new->str[i] = fm->str[i];
    }
    new->str[new_len] = '\0';

    string_destroy(filename);
    *filename = new;
}

void trim_file_start(string** url, string* start)
{
    string* fm = *url;
    int new_len = fm->len - start->len;
    string* new = string_alloc(new_len);

    for(int i = 0; i <= new_len; i++)
    {
        new->str[i] = fm->str[i+start->len];
    }

    string_destroy(url);
    *url = new;
}
