#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <stdexcept>

class BitcoinExchange {
public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();

    void loadDatabase(); // Notez le changement ici : plus besoin d'argument

    double getValueAt(const std::string& date, double amount) const;

private:
    std::map<std::string, double> exchangeRates;
    bool isValidDate(const std::string& date) const;
    bool isLeapYear(int year) const;
    bool isDateValid(int year, int month, int day) const;
};

#endif // BITCOINEXCHANGE_HPP
