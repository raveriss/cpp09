#include "../incs/BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : exchangeRates(other.exchangeRates) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other) {
        exchangeRates = other.exchangeRates;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::loadDatabase() {
    // Chargement manuel des taux de change
    exchangeRates["2011-01-03"] = 0.1;
    exchangeRates["2011-01-09"] = 0.32;
    exchangeRates["2012-01-11"] = 7.1;
    // Ajouter d'autres taux de change si nécessaire
}

double BitcoinExchange::getValueAt(const std::string& date, double amount) const {
    if (!isValidDate(date)) {
        throw std::invalid_argument("Error: bad input => " + date);
    }

    if (amount < 0) {
        throw std::domain_error("Error: not a positive number.");
    }

    if (amount > 1000) {
        throw std::out_of_range("Error: too large a number.");
    }

    std::map<std::string, double>::const_iterator it = exchangeRates.lower_bound(date);
    if (it == exchangeRates.end() || it->first != date) {
        if (it != exchangeRates.begin()) {
            --it;
        } else {
            throw std::runtime_error("Error: date not found.");
        }
    }

    return amount * it->second;
}

bool BitcoinExchange::isValidDate(const std::string& date) const {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }
    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (year < 0 || year > 9999) {
        return false;
    }

    return isDateValid(year, month, day);
}

bool BitcoinExchange::isLeapYear(int year) const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool BitcoinExchange::isDateValid(int year, int month, int day) const {
    if (month < 1 || month > 12) {
        return false;
    }

    static const int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int days = daysInMonth[month - 1];

    if (month == 2 && isLeapYear(year)) {
        days = 29;
    }

    return day >= 1 && day <= days;
}
