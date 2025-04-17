// curl_helpers.cpp
// Contains the callback function used by cURL to write HTTP response data into a std::string

#include "curl_helpers.h"

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}
