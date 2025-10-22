#include "../../include/download/parallel.h"
#include "../../include/download/download.h"
#include "../../include/init.h"
#include "../../include/io.h"
#include "../../include/args.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void spawn_child_process(CURL* curl, string** url)
{
    if(*url == NULL)
    {
        printf("FATAL: URL is null!\n");
        exit(1);
    }
        
    int i = perform_single_download(*url, curl);

    curl_cleanup(curl);
    string_destroy(url);
    exit(i);
}

void wait_for_child(pid_t * ids, int i, int n, int *active_children, vec_t* urls)
{
    int status;
    waitpid(ids[i % n], &status, 0);
    int relidx = i - (*active_children);
    string* relurl = vec_get(urls, relidx);
    if(status == 0)
    {
        printf("%d - Url %s baixado com sucesso!\n", 
               relidx, 
               relurl->str);
    }
    else 
    {
        printf("%d - Falha ao baixar o url %s!\n", 
               relidx, 
               relurl->str);
    }

    (*active_children)--;
}

void perform_multiple_download(vec_t** vecp, CURL* curl)
{
    file_t* textfile;
    int n = 4;

    validate_flags(vecp, &n, &textfile);
    vec_t* urls = parse_url_file(&textfile);

    pid_t ids[n];
    int active_children = 0;
    int i;

    for(i = 0; i < vec_size(urls); i++)
    {
        if(active_children == n)
        {
            wait_for_child(ids, i, n, &active_children, urls);
        }

        pid_t pid = fork();
        if(pid == 0)
        {
            string* url = vec_get(urls, i);
            spawn_child_process(curl, &url);
        }
        ids[i % n] = pid;
        active_children++;
    }

    while(active_children != 0)
    {
        wait_for_child(ids, i, n, &active_children, urls);
    }

    vec_destroy(&urls);
}
