#include "../include/string/string.h"
#include "../include/string/extension.h"
#include "../include/file.h"
#include <stdio.h>
#include "../include/vec.h"
#include <string.h>

string* parse_url_name(string* url)
{
    string* filename = string_copy(url);

    string* start = get_file_start(filename);
    string* ext = get_file_extension(filename);
    string* startend = string_new("://");
    string* fullstart = string_concat(&start, &startend);

    trim_file_start(&filename, fullstart);
    trim_file_extension(&filename, ext);

    string_replace(&filename, "/.", '_');
    string_destroy(&fullstart);
    
    return string_concat(&filename, &ext);
}

vec_t* parse_url_file(file_t** file)
{
    vec_t* str_vec = vec_new(STR);
    char buf[256];

    while (fgets(buf, 256, (*file)->fp)) 
    {
        buf[strcspn(buf, "\n")] = 0;
        vec_add(str_vec, string_new(buf));
    }
    
    file_close(file);
    return str_vec;
}
