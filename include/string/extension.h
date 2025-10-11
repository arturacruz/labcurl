#ifndef EXTENSION_H
#define EXTENSION_H

#include "string.h"

string* get_file_extension(string* url);
string* get_file_start(string* url);
void trim_file_extension(string *filename, string* ext);
void trim_file_start(string* url, string* start);

#endif // !EXTENSION_H
