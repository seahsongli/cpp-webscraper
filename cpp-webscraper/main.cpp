#include "cpp-webscraper.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <future>
std::string get_request_from_new_scrapper(const std::string& url)
{
    WebScraper scrapper;
    return scrapper.get_request(url);
}

int main()
{
    // Initialse curl globally
    auto start = std::chrono::high_resolution_clock::now();
    WebScraper scrapper;

    std::string crypto_page = scrapper.get_request("https://sg.finance.yahoo.com/crypto/");
    std::string currencies_page = scrapper.get_request("https://sg.finance.yahoo.com/topic/currencies/");
    std::string commodities_page = scrapper.get_request("https://sg.finance.yahoo.com/topic/commodities/");
    
    scrapper.save_to_file(crypto_page, "crypto_page.html");
    scrapper.save_to_file(currencies_page, "currencies_page.html");
    scrapper.save_to_file(commodities_page, "commodities_page.html");

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Duration without mulithread: " << duration.count() << " milliseconds" << std::endl;

    
    auto future_crypto = std::async(std::launch::async, get_request_from_new_scrapper, "https://sg.finance.yahoo.com/crypto/");
    auto future_currencies = std::async(std::launch::async, get_request_from_new_scrapper, "https://sg.finance.yahoo.com/topic/currencies/");
    auto future_commodities = std::async(std::launch::async, get_request_from_new_scrapper, "https://sg.finance.yahoo.com/topic/commodities/");
    start = std::chrono::high_resolution_clock::now();
    
    // Note that .get() blocks the main thread.
    std::string crypto_page_multithreaded = future_crypto.get();
    std::string currencies_page_multithreaded = future_currencies.get();
    std::string commodities_page_multithreaded = future_commodities.get();
   
    scrapper.save_to_file(crypto_page_multithreaded, "crypto_page_multithreaded.html");
    scrapper.save_to_file(currencies_page_multithreaded, "currencies_page_multithreaded.html");
    scrapper.save_to_file(commodities_page_multithreaded, "commodities_page_multithreaded.html");
  
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Duration with mulithread: " << duration.count() << " milliseconds" << std::endl;
    return 0;
}