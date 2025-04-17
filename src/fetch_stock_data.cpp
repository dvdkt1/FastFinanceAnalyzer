// fetch_stock_data.cpp
// Fetches daily stock data (OHLC + volume) from Alpha Vantage API
// Saves the results to a CSV file for downstream use

#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <cstdlib>
#include "curl_helpers.h"
#include <chrono>
#include <thread>

using json = nlohmann::json;

void fetch_and_process_stock_data(const std::string& symbol) {
    CURL* curl;
    CURLcode res;

    // Load API key from environment variable
    const char* env_key = std::getenv("FAST_FINANCE_API_KEY");

    if (!env_key) {
        std::cerr << "Environment variable FAST_FINANCE_API_KEY not set." << std::endl;
        return;
    }
    std::string apiKey = env_key;

    // Construct Alpha Vantage API request URL
    std::string url = "https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=" +
                      symbol + "&apikey=" + apiKey;
    std::string response;

    // Wait to avoid hitting rate limits
    std::this_thread::sleep_for(std::chrono::seconds(15));

    curl = curl_easy_init();
    if (curl) {
        // Set cURL options
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res == CURLE_OK) {
            // Parse the response JSON
            json stock_data = json::parse(response);

            if (stock_data.contains("Time Series (Daily)")) {
                // Write to CSV
                std::ofstream file("../data/" + symbol + "_data.csv");
                file << "Date,Open,High,Low,Close,Volume\n";

                for (auto& [date, values] : stock_data["Time Series (Daily)"].items()) {
                    file << date << "," 
                    << values["1. open"] << ","
                    << values["2. high"] << ","
                    << values["3. low"] << ","
                    << values["4. close"] << ","
                    << values["5. volume"] << "\n";
                }

                file.close();
                std::cout << "Stock data saved as CSV: ../data/" << symbol << "_data.csv" << std::endl;
            } else {
                std::cerr << "API error or rate limit hit for: " << symbol << std::endl;
                std::cerr << "Response: " << stock_data.dump(2) << std::endl;
            }
        }
    }
}

