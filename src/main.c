#include <curl/curl.h>

#include "../include/args.h"
#include "../include/download.h"
#include "../include/flag.h"
#include "../include/vec.h"
#include "../include/init.h"
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) 
{
    CURL* curl = curl_init();

    vec_t* flag_vec = validate_args(argc, argv);

    flag_t* first_flag = vec_get(flag_vec, 0);
    if(first_flag->flag == NULL) 
    {
        perform_single_download(first_flag->content, curl);
        vec_destroy(&flag_vec);
        curl_cleanup(curl);
        return 0;
    }

    perform_multiple_download(&flag_vec, curl);
    curl_cleanup(curl);

    // Wait for all children to DIE
    while(wait(NULL) > 0);
    return 0;
}
