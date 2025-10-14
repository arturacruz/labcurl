#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <curl/curl.h>
#include "string/string.h"
#include "file.h"
#include "flag.h"
#include "vec.h"

int download_file(CURL* curl, file_t** file, string* url);
void perform_single_download(string* url, CURL* curl);
void perform_multiple_download(vec_t** vec, CURL* curl);

#endif // !DOWNLOAD_H
