#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <cstdlib>

using json = nlohmann::json;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

void fetch_and_process_stock_data(const std::string& symbol) {
    CURL* curl;
    CURLcode res;
    std::string apiKey = std::getenv("FAST_FINANCE_API_KEY");
    std::string url = "https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=" +
                      symbol + "&apikey=" + apiKey;
    std::string response;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res == CURLE_OK) {
            json stock_data = json::parse(response);

            // ✅ Extract time series data
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
            std::cout << "✅ Stock data saved as CSV: data/" << symbol << "_data.csv" << std::endl;
        } else {
            std::cerr << "❌ cURL Error: " << curl_easy_strerror(res) << std::endl;
        }
    }
}

int main() {
    fetch_and_process_stock_data("AAPL");  // Fetch and process Apple stock data
    return 0;
}

