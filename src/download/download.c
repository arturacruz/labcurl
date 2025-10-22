#include <curl/curl.h>
#include "../../include/string/string.h"
#include "../../include/file.h"
#include "../../include/io.h"
#include "../../include/string/string.h"
#include <unistd.h>
#include <sys/wait.h>

int download_file(CURL* curl, file_t** file, string* url)
{
    curl_easy_setopt(curl, CURLOPT_URL, url->str);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (*file)->fp);
    int resultado = curl_easy_perform(curl);

    file_close(file);
    if(resultado != 0)
    {
        remove((*file)->filename->str);
    }
    file_destroy(file);
    return resultado;
}

int perform_single_download(string* url, CURL* curl)
{
    string* filename = parse_url_name(url);
    file_t* file = file_open(filename);

    int res = download_file(curl, &file, url);
    string_destroy(&filename);
    return res;
}





