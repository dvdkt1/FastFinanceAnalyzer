# FastFinanceAnalyzer

**FastFinanceAnalyzer** is a high-speed financial data processor that fetches real-time cryptocurrency and stock market data using multithreaded C++. The data is exported to CSV files for downstream analysis in Python using machine learning models and statistical techniques.

---

##  Features

-  **Multithreaded API Fetching** — parallel fetching for both stocks and crypto
-  **Cryptocurrency Data** via CoinGecko
-  **Stock Market Data** via Alpha Vantage
-  Outputs CSVs with key financial metrics (price, volume, OHLC)
-  Python notebook included for machine learning analysis

---

##  Motivation

FastFinanceAnalyzer was built to provide a lightweight, efficient foundation for:
- Quantitative finance research
- Machine learning experiments on financial data
- Building predictive models and visualizations

---

##  Project Structure

<pre>
FastFinanceAnalyzer/
├── src/
│   ├── curl_helpers.cpp
│   ├── curl_helpers.h
│   ├── fetch_crypto_data.cpp
│   ├── fetch_crypto_data.h
│   ├── fetch_stock_data.cpp
│   ├── fetch_stock_data.h
│   └── main_multithreaded_fetch.cpp
├── financial_analysis.ipynb
├── .env
├── .gitignore
├── LICENSE
└── README.md
</pre>
---

##  Requirements

- **C++17+**
- `libcurl` installed
- Python 3.x (for Jupyter notebook analysis)
- Python libraries: `pandas`, `matplotlib`, `sklearn`, `seaborn`, `numpy`

---

##  API Setup

Create a `.env` file in the root directory with your API key:
FAST_FINANCE_API_KEY=your_alphavantage_api_key


> CoinGecko API does not require authentication for public endpoints.

---

##  How to Run

### Compile & Execute (C++)
```bash
cd src
g++ -std=c++17 -lcurl -pthread *.cpp -o fetcher
./fetcher

# Launch the notebook
jupyter notebook financial_analysis.ipynb

# Data
data/bitcoin_hourly.csv
data/AAPL_data.csv

```

## Author

**David Kennet**

---

## Roadmap

- [ ] Add CLI support for symbol/days
- [ ] Retry logic for failed API calls
- [ ] SQLite or Parquet backend for storage
