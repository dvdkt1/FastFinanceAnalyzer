// fetch_crypto_data.cpp
// Fetches historical hourly cryptocurrency data (price and volume) from the CoinGecko API
// Saves results to a CSV file for downstream analysis

#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <cstdlib>
#include "curl_helpers.h"

using json = nlohmann::json;

void fetch_crypto_data(const std::string& coin_id, int days) {
    CURL* curl;
    CURLcode res;
    std::string response;

    // Construct the CoinGecko API request URL
    std::string url = "https://api.coingecko.com/api/v3/coins/" + coin_id +
                      "/market_chart?vs_currency=usd&days=" + std::to_string(days) +
                      "";

    curl = curl_easy_init();
    if (curl) {
        // Set cURL options
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res == CURLE_OK) {
            // Parse JSON response
            json data = json::parse(response);

            std::cout << "data[\"prices\"] size: " << data["prices"].size() << std::endl;
            std::cout << "data[\"total_volumes\"] size: " << data["total_volumes"].size() << std::endl;

            // Write to CSV
            std::ofstream file("../data/" + coin_id + "_hourly.csv");
            file << "Timestamp,Price,Volume\n";

            for (size_t i = 0; i < data["prices"].size(); ++i) {
                long long timestamp = data["prices"][i][0];
                double price = data["prices"][i][1];
                double volume = data["total_volumes"][i][1];
                file << timestamp << "," << price << "," << volume << "\n";
            }

            file.close();
            std::cout << "Saved: ../data/" << coin_id << "_hourly.csv" << std::endl;
        } else {
            std::cerr << "cURL Error: " << curl_easy_strerror(res) << std::endl;
        }
    } else {
        std::cerr << "Failed to initialize cURL\n";
    }
}