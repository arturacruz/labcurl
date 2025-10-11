
#include "../include/file.h"
#include "../include/string.h"
#include <stdlib.h>

file_t* file_open(string* filename)
{
    FILE* file = fopen(filename->str, "wb");

    file_t* ft = malloc(sizeof(file_t));
    ft->fp = file;
    ft->filename = filename;
    return ft;
}

void file_close(file_t** file)
{
    fclose((*file)->fp);
    string_destroy(&(*file)->filename);
    free(*file);
}
