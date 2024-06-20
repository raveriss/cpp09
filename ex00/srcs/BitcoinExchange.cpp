/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 23:48:56 by raveriss          #+#    #+#             */
/*   Updated: 2024/06/21 00:13:58 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Inclure les fichiers pour la classe BitcoinExchange */
#include "../incs/BitcoinExchange.hpp"

/* Inclure les fichiers pour std::ifstream */
#include <fstream>

/* Inclure les fichiers pour std::istringstream */
#include <sstream>

/* Inclure les fichiers pour l'utilisation de cout */
#include <iostream>

/* Inclure les fichiers pour std::runtime_error */
#include <iomanip>

/* Inclure les fichiers pour std::atoi */
#include <cstdlib>

/* Constructeur par défaut */
BitcoinExchange::BitcoinExchange()
{}

/* Constructeur par copie */
BitcoinExchange::BitcoinExchange(const BitcoinExchange & other)
: exchangeRates(other.exchangeRates)
{}

/* Surcharge de l'opérateur = */
BitcoinExchange & BitcoinExchange::operator = (const BitcoinExchange & other)
{
    if (this != &other)
        exchangeRates = other.exchangeRates;

    return *this;
}

/* Destructeur */
BitcoinExchange::~BitcoinExchange()
{}

/**
 * @brief Fonction pour charger la base de données
 */
void BitcoinExchange::loadDatabase(const std::string& filename)
{
    std::ifstream file(filename.c_str());

    if (!file.is_open())
        throw std::runtime_error("Error: could not open file.");

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string date;
        double rate;
        char delimiter;

        if (iss >> date >> delimiter >> rate && delimiter == ',')
            exchangeRates[date] = rate;
    }
    file.close();
}

/**
 * @brief Fonction pour obtenir la valeur à une date donnée
 */
double BitcoinExchange::getValueAt(const std::string& date, double amount) const
{
    if (!isValidDate(date))
        throw std::invalid_argument("Error: bad input => " + date);

    if (amount < 0 || amount > 1000)
        throw std::out_of_range("Error: value out of range.");

    std::map<std::string, double>::const_iterator it = exchangeRates.lower_bound(date);
    if (it == exchangeRates.end() || it->first != date)
    {
        if (it != exchangeRates.begin())
            --it;
        else
            throw std::runtime_error("Error: date not found.");
    }

    return amount * it->second;
}

/**
 * @brief Fonction pour vérifier si une date est valide
 */
bool BitcoinExchange::isValidDate(const std::string& date) const
{
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (year < 0 || year > 9999)
        return false;

    return isDateValid(year, month, day);
}

/**
 * @brief Fonction pour vérifier si une année est bissextile
 */
bool BitcoinExchange::isLeapYear(int year) const
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

/**
 * @brief Fonction pour vérifier si une date est valide
 */
bool BitcoinExchange::isDateValid(int year, int month, int day) const
{
    if (month < 1 || month > 12)
        return false;

    static const int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int days = daysInMonth[month - 1];

    if (month == 2 && isLeapYear(year))
        days = 29;

    return day >= 1 && day <= days;
}

/* BitcoinExchange.cpp */
