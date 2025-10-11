#include <curl/curl.h>
#include <stdlib.h>

#include "../include/io.h"

#define USERAGENT "Mozilla/5.0 (X11; Linux x86_64; rv:60.0) Gecko/20100101 Firefox/81.0"

CURL* curl_init(string* url, string **filename) 
{
    CURL *curl = curl_easy_init();
    if(curl == NULL) 
    {
        printerr("Failed to initialize curl.\n");
        exit(1);
    }

    *filename = parse_url_name(url);

    curl_easy_setopt(curl, CURLOPT_USERAGENT, USERAGENT);
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);

    return curl;
}

void curl_cleanup(CURL* curl)
{
    curl_easy_cleanup(curl);
}
