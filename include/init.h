#ifndef INIT_H
#define INIT_H

#include <curl/curl.h>
#include <stdio.h>
#include "../include/string.h"

CURL* curl_init(string* url, string **filename);

void curl_cleanup(CURL* curl);

#endif
