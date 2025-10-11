#include <curl/curl.h>
#include "../include/string.h"
#include "../include/file.h"
#include "../include/io.h"

int download_file(CURL* curl, file_t** file, string* url)
{
    printf("Downloading file to %s\n", (*file)->filename->str);
    curl_easy_setopt(curl, CURLOPT_URL, url->str);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (*file)->fp);
    int resultado = curl_easy_perform(curl);
    if(resultado == CURLE_OK)
        printf("File %s downloaded successfully!\n", url->str);
    else
        printerr("ERROR: %s\n", curl_easy_strerror(resultado));

    file_close(file);
    return resultado;
}
