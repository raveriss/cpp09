#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <string>

class BitcoinExchange {
public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();

    void loadDatabase(const std::string& filename);
    void processInput(const std::string& filename);
    double getExchangeRate(const std::string& date) const;

private:
    std::map<std::string, double> exchangeRates;
    bool isValidDate(const std::string& date) const;
    bool isValidValue(const std::string& value) const;
};

#endif // BITCOINEXCHANGE_HPP
