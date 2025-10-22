#include "../../include/flag/flag.h"
#include <stdlib.h>
#include <string.h>
#include "../../include/string/string.h"
#include "../../include/file.h"
#include "../../include/io.h"
#include "../../include/string/extension.h"

flag_t* flag_new(char* flag, char* content)
{
    flag_t* f = malloc(sizeof(flag_t));
    if(flag == NULL)
    {
        f->flag = NULL;
    }
    else 
    {
        f->flag = string_new(flag);
    }
    f->content = string_new(content);

    return f;
}

bool is_flag(char* flag)
{
    if(strlen(flag) < 2)
        return false;
    return flag[0] == '-' && flag[2] == '\0';
}

void flag_destroy(flag_t** flag)
{
    flag_t* fp = *flag;
    if(fp->flag != NULL)
    {
        string_destroy(&fp->flag);
    }
    string_destroy(&fp->content);
    free(*flag);
    *flag = NULL;
}

file_t* flag_f(flag_t* curr) 
{
    string* fileext = get_file_extension(curr->content);
    if(!string_compare_str(fileext, ".txt"))
    {
        printerr("Flag -f requires a .txt file (labcurl -f downloads.txt).\n");
        exit(1);
    }

    string_destroy(&fileext);
    return file_read(curr->content);
}

int flag_n(flag_t* curr)
{
    int res = atoi(curr->content->str);
    if(res == 0)
    {
        printerr("Error using %s as -n flag. N should be a number.\n", curr->content->str);
        exit(1);
    }
    return res;
}
