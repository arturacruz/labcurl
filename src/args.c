#include "../include/string/string.h"
#include "../include/string/extension.h"
#include "../include/flag/flag.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "../include/io.h"

void check_url(char* ur) 
{
    string* url = string_new(ur);
    string* start = get_file_start(url);
    if(!strcmp(start->str, "http") && !strcmp(start->str, "https")) 
    {
        printerr("The received url is invalid, does not start with http:// or https://.");
        exit(1);
    }
    string_destroy(&start);
    string_destroy(&url);
}

// Returns the size of arr
vec_t* validate_args(int argc, char** argv)
{
    if(argc <= 1)
    {
        printerr("Incorrect arguments. Usage: labcurl URL\n");  
        exit(1); 
    }

    vec_t* vec = vec_new(FLAG);
    // If usage is only labcurl URL, no flags.
    if(argc == 2) 
    {
        char* url = argv[1];
        if(url[0] == '-') 
        {
            printerr("Bad usage of flag %s.\n", url);
            exit(1);
        }
        check_url(url);

        vec_add(vec, flag_new(NULL, url));
        return vec;
    }

    bool next_flag = false;
    for(int i = 1; i < argc; i++) 
    {
        char* curr = argv[i];
        if(next_flag) 
        {
            vec_add(vec, flag_new(argv[i-1], curr));
            next_flag = false;
        }
        else if(is_flag(curr))
        {
            next_flag = true;
        }
        else 
        {
            printerr("Not a valid parameter %s.\n", curr);
            exit(1);
        }
    }

    return vec;
}

void validate_flags(vec_t** flags, int* n, file_t** file)
{
    *n = 4;
    for(int i = 0; i < vec_size(*flags); i++)
    {
        flag_t* curr = vec_get(*flags, i);
        // NO Flag
        if(curr == NULL)
        {
            printf("NO FLAG\n");
            continue;
        }

        // -f FLAG
        //
        else if(string_compare_str(curr->flag, "-f"))
        {
            *file = flag_f(curr);
        }

        // -n FLAG
        
        else if(string_compare_str(curr->flag, "-n"))
        {
            *n = flag_n(curr);
        }
        else 
        {
            printerr("Unknown flag %s.\n", curr->flag->str);
            exit(1);
        }
    }

    if(*file == NULL) 
    {
        printerr("No file to multiple download provided (-f file.txt).");
        exit(1);
    }
    vec_destroy(flags);
}
