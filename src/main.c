#include <curl/curl.h>

#include "../include/init.h"
#include "../include/string.h"
#include "../include/args.h"
#include "../include/file.h"
#include "../include/download.h"

int main(int argc, char **argv) 
{
    // string* url = validate_args(argc, argv);
    //
    // string* filename;
    //
    // CURL* curl = curl_init(url, &filename);
    //
    // file_t* file = file_open(filename);
    //
    // download_file(curl, &file, url);
    
    // curl_cleanup(curl);
    //
    string* a = string_new("abc");
    string* b = string_new("def");
    string* c = string_concat(&a, &b);
    printf("%s\n", c->str);
}
