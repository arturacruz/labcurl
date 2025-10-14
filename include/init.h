#ifndef INIT_H
#define INIT_H

#include <curl/curl.h>

CURL* curl_init(void);

void curl_cleanup(CURL* curl);

#endif
