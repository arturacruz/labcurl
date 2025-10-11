#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <curl/curl.h>
#include "string.h"
#include "file.h"

int download_file(CURL* curl, file_t** file, string* url);

#endif // !DOWNLOAD_H
