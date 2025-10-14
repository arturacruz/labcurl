#include "../include/flag.h"
#include <stdlib.h>
#include "../include/string/string.h"

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
