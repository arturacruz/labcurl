#include <curl/curl.h>
#include "../include/string/string.h"
#include "../include/file.h"
#include "../include/io.h"
#include "../include/flag.h"
#include "../include/string/string.h"
#include "../include/vec.h"
#include "../include/string/extension.h"
#include "../include/init.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

void spawn_child_process(CURL* curl, vec_t** vecp, int start, int limit)
{

    for(int i = start; i < limit; i++)
    {
        string* url = vec_get(*vecp, i);
        if(url == NULL)
        {
            printf("FATAL: URL is null at %d!\n", i);
            exit(1);
        }
        printf("%d - ", i + 1);
            
        perform_single_download(url, curl);
    }
    vec_destroy(vecp);
    curl_cleanup(curl);
    exit(0);
}

int* calculate_children_load(int n, int size)
{
    int global_load = size / n;
    int rest = size - (n * global_load);
    int* loads = malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++)
    {
        int load = global_load;
        if(rest != 0)
        {
            load++;
            rest--;
        }
        loads[i] = load;
    }
    return loads;
}

void perform_multiple_download(vec_t** vecp, CURL* curl)
{
    file_t* textfile;
    vec_t* vec = *vecp;
    int n = 4;
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
        else if(string_compare_str(curr->flag, "-f"))
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

        // -n FLAG
        
        else if(string_compare_str(curr->flag, "-n"))
        {
            int res = atoi(curr->content->str);
            if(res == 0)
            {
                printerr("Error using %s as -n flag. N should be a number.\n", curr->content->str);
                exit(1);
            }
            n = res;
        }
        else 
        {
            printerr("Unknown flag %s.\n", curr->flag->str);
            exit(1);
        }
    }

    if(textfile == NULL) 
    {
        printerr("No file to multiple download provided (-f file.txt).");
        exit(1);
    }

    vec_t* urls = parse_url_file(&textfile);
    int size = vec_size(urls);
    int* loads = calculate_children_load(n, size);
    int end = 0;

    for(int i = 0; i < n; i++)
    {
        int load = loads[i];
        pid_t pid = fork();
        if(pid == 0)
        {
            spawn_child_process(curl, &urls, end, end + load);
        }
        end += load;
    }
    free(loads);

    vec_destroy(&urls);
    vec_destroy(vecp);
}


