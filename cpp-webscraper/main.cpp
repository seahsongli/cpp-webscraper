#include "cpp-webscraper.h"
#include <iostream>
int main()
{
    // Initialse curl globally
    WebScraper scrapper;
    std::string html_document = scrapper.get_request("https://finance.yahoo.com/");
    scrapper.save_to_file(html_document, "output.html");
    return 0;
}