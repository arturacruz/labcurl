#include "../include/file.h"
#include "../include/string/string.h"
#include "../include/io.h"
#include <stdlib.h>
#include <stdbool.h>

file_t* file_open(string* filename)
{
    FILE* file = fopen(filename->str, "wb");
    if(file == NULL)
    {
        printerr("Failed to open file %s.\n", filename->str);
        exit(1);
    }

    file_t* ft = malloc(sizeof(file_t));
    ft->fp = file;
    ft->filename = string_copy(filename);
    return ft;
}

file_t* file_read(string* filename)
{
    FILE* file = fopen(filename->str, "r");
    if(file == NULL)
    {
        printerr("Failed to open file %s.\n", filename->str);
        exit(1);
    }

    file_t* ft = malloc(sizeof(file_t));
    ft->fp = file;
    ft->filename = string_copy(filename);
    return ft;
}

void file_close(file_t** file)
{
    fclose((*file)->fp);
    string_destroy(&(*file)->filename);
    free(*file);
}
