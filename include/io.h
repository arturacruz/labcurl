#ifndef IO_H
#define IO_H

#include <stdio.h>
#include "string/string.h"
#include "file.h"
#include "vec.h"

#define printerr(...) fprintf(stderr, __VA_ARGS__); 

string* parse_url_name(string* url);
vec_t* parse_url_file(file_t** file);

#endif
