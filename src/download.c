#include <curl/curl.h>
#include "../include/string/string.h"
#include "../include/file.h"
#include "../include/io.h"
#include "../include/flag.h"
#include "../include/string/string.h"
#include "../include/vec.h"
#include "../include/string/extension.h"
#include <stdlib.h>

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

void perform_single_download(string* url, CURL* curl)
{
    string* filename = parse_url_name(url);
    file_t* file = file_open(filename);

    download_file(curl, &file, url);
    string_destroy(&filename);
}

void perform_multiple_download(vec_t** vecp, CURL* curl)
{
    file_t* textfile;
    vec_t* vec = *vecp;
    for(int i = 0; i < vec->size; i++)
    {
        flag_t* curr = vec_get(vec, i);

        // NO Flag
        if(curr == NULL)
        {
            printf("NO FLAG\n");
            continue;
        }

        // -f FLAG
        //
        if(string_compare_str(curr->flag, "-f"))
        {
            string* fileext = get_file_extension(curr->content);
            if(!string_compare_str(fileext, ".txt"))
            {
                printerr("Flag -f requires a .txt file (labcurl -f downloads.txt).\n");
                exit(1);
            }

            textfile = file_read(curr->content);
            string_destroy(&fileext);
        }

        // TODO: -n FLAG
    }

    if(textfile == NULL) 
    {
        printerr("No file to multiple download provided.");
        exit(1);
    }

    
    vec_t* urls = parse_url_file(&textfile);
    for(int i = 0; i < vec_size(urls); i++)
    {
        string* url = vec_get(urls, i);
        perform_single_download(url, curl);
    }

    vec_destroy(vecp);
}
