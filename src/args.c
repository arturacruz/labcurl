#include "../include/string.h"
#include <stdlib.h>
#include "../include/io.h"

string* validate_args(int argc, char** argv)
{
    if(argc != 2)
    {
        printerr("Incorrect arguments. Usage: labcurl URL\n");  
        exit(1); 
    }

    string* url = string_new(argv[1]);
    //
    // if(!string_validate_url_start(url)) 
    // {
    //     printerr("The received url is invalid, does not start with http:// or https://.");
    //     exit(1);
    // }

    return url;
}
