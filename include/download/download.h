#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <curl/curl.h>
#include "../string/string.h"
#include "../file.h"
#include "../flag/flag.h"
#include "../vec.h"

int download_file(CURL* curl, file_t** file, string* url);
int perform_single_download(string* url, CURL* curl);

#endif // !DOWNLOAD_H
