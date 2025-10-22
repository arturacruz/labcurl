#ifndef FILE_H
#define FILE_H

#include "string/string.h"
#include <stdio.h>

typedef struct {
    FILE* fp;
    string* filename;
} file_t;

file_t* file_open(string* filename);
file_t* file_read(string* filename);
void file_close(file_t** file);
void file_destroy(file_t** file);

#endif // !FILE_H
