#include "../include/string.h"

string* parse_url_name(string* url)
{
    string* filename = string_copy(url);

    // string_trim_url_start(&filename);
    // // if(string_ends_in_html(filename))
    // // {
    // //     string_trim_url_end(&filename);
    // // }
    // string_trim_url_end(&filename);


    string_replace(&filename, "/.", '_');
    return filename;
}
