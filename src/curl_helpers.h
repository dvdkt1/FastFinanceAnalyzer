// curl_helpers.h
// Header for cURL write callback used in all fetch functions

#ifndef CURL_HELPERS_H
#define CURL_HELPERS_H

#include <string>

// Callback function for cURL to write received data into a std::string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output);

#endif