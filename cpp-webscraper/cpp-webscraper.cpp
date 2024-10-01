#include <iostream> 
#include <string.h>
#include <curl/curl.h>
#include "libxml/HTMLparser.h"
#include "libxml/xpath.h"

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response)
{
    size_t totalSize = size * nmemb;
    response->append((char*)contents, totalSize);
    return totalSize;
}
std::string get_request(std::string url)
{
    CURL* curl = curl_easy_init();
    std::string result;

    if (curl)
    {
        CURLcode res;

        // setopt is used to tell libcurl how to behave.
        // CURLOPT_WRITEFUNCTION => Pointer, we need to allocate a callback function to this pointer
        // CURLOPT_WRITEDATA => Tells libucrl where to store the data received from server
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // c_str to convert C++ string to C_Style strings. 
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); // Set the write callback function.
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.114 Safari/537.36"); // to prevent access from being denied.

        // This would execute all the options we have set
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

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
    std::cout << html_document << std::endl;

    curl_global_cleanup();
    return 0;
}