#include <iostream> 
#include <string.h>
#include <curl/curl.h>
#include "libxml/HTMLparser.h"
#include "libxml/xpath.h"

std::string get_request(std::string url)
{
    CURL* curl = curl_easy_init();
    std::string result;
    if (curl)
    {
        CURLcode res;

        // setopt is used to tell libcurl how to behave.
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // c_str to convert C++ string to C_Style strings. 
        res = curl_easy_perform(curl);
        
        // write the data we got into the variable result
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
        curl_easy_perform(curl);

        // free up curl resources
        curl_easy_cleanup(curl);
    }
    return result;
}
int main()
{
    // Initialse curl globally
    curl_global_init(CURL_GLOBAL_ALL);

    std::string html_document = get_request("https://www.scrapingcourse.com/ecommerce/");
    std::cout << html_document;

    curl_global_cleanup();
    return 0;
}