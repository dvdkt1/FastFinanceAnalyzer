// fetch_stock_data.h
// Header for fetching stock data from Alpha Vantage

#ifndef FETCH_STOCK_DATA_H
#define FETCH_STOCK_DATA_H

#include <string>

// Fetches daily stock data for a given symbol using Alpha Vantage
void fetch_and_process_stock_data(const std::string& symbol);

#endif