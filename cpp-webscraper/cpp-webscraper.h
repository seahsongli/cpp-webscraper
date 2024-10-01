#pragma once

#include <iostream> 
#include <string.h>
#include <fstream>
#include <curl/curl.h>
#include "libxml/HTMLparser.h"
#include "libxml/xpath.h"

class WebScraper
{
public:
	WebScraper();
	~WebScraper();

	void save_to_file(const std::string& content, const std::string& filename);
	std::string get_request(const std::string& url);

private:
	CURL* curl;
	static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response);
};