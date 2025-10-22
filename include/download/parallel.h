#ifndef PARALLEL_H
#define PARALLEL_H

#include "../vec.h"
#include <curl/curl.h>

void perform_multiple_download(vec_t** vec, CURL* curl);

#endif
