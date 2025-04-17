// fetch_crypto_data.h
// Header for fetching cryptocurrency data from CoinGecko

#ifndef FETCH_CRYPTO_DATA_H
#define FETCH_CRYPTO_DATA_H

#include <string>

// Fetches hourly crypto data for the given coin ID and number of days
void fetch_crypto_data(const std::string& coin_id, int days);

#endif