
#include "fetcher.hpp"

#include <curl/curl.h>
#include <string>
#include <iostream>


static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string fetchPage(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            std::cerr << "failed to fetch " << url << ": " << curl_easy_strerror(res) << "\n";
        curl_easy_cleanup(curl);
    }
    return readBuffer;
    
}