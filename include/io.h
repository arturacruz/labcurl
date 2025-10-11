#ifndef IO_H
#define IO_H

#include <stdio.h>
#include "string.h"

#define printerr(...) fprintf(stderr, __VA_ARGS__); 

string* parse_url_name(string* url);

#endif
