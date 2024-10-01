// cpp-webscraper.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response);
std::string get_request(std::string url)
// TODO: Reference additional headers your program requires here.
