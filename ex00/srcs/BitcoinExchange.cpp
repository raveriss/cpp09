/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:53:54 by raveriss          #+#    #+#             */
/*   Updated: 2024/06/21 20:15:11 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Inclusion de la classe BitcoinExchange */
#include "BitcoinExchange.hpp"

/* Inclusion de la bibliothèque standard pour std::ifstream */
#include <fstream>

/* Inclusion de la bibliothèque standard pour std::sstream */
#include <sstream>

/* Inclusion de la bibliothèque standard pour std::runtime_error */
#include <stdexcept>

/* Inclure les fichiers pour les limites des types */
#include <limits>

/* Inclure les fichiers pour les limites des types */
#include <cstdlib> // Pour atof et strtod

/* Inclusion de la bibliothèque standard pour std::cout */
#include <iostream>

/**
 * @brief Constructeur par défaut
 */
BitcoinExchange::BitcoinExchange()
{}

/**
 * @brief Constructeur par copie
 */
BitcoinExchange::BitcoinExchange(const BitcoinExchange & other)
: _exchangeRates(other._exchangeRates)
{}

/**
 * @brief Opérateur d'affectation
 */
BitcoinExchange & BitcoinExchange::operator = (const BitcoinExchange & other)
{
    if (this != & other)
        _exchangeRates = other._exchangeRates;
    return *this;
}

/**
 * @brief Destructeur
 */
BitcoinExchange::~BitcoinExchange()
{}

/**
 * @brief Charge la base de données
 */
void BitcoinExchange::loadDatabase(const std::string & filename)
{
    std::ifstream file(filename.c_str());
    if (!file)
        throw std::runtime_error("Error: could not open file.");

    std::string line, date;
    double rate;
    getline(file, line); // skip the header
    while (getline(file, line))
    {
        std::stringstream ss(line);
        if (getline(ss, date, ',') && (ss >> rate))
            _exchangeRates[date] = rate;
    }
}

/**
 * @brief Traite l'entrée
 */
void BitcoinExchange::processInput(const std::string & filename)
{
    std::ifstream file(filename.c_str());
    if (!file)
        throw std::runtime_error("Error: could not open file.");
        
    std::string line, date, valueStr;
    double value;
    getline(file, line); // skip the header
    while (getline(file, line))
    {
        std::stringstream ss(line);
        if (getline(ss, date, '|'))
        {
            if (!getline(ss, valueStr))
            {
                std::cout << "Error: bad input => " << line << std::endl;
                continue;
            }
            date.erase(date.find_last_not_of(" \n\r\t") + 1);
            valueStr.erase(0, valueStr.find_first_not_of(" \n\r\t"));
            if (!isValidDate(date))
            {
                std::cout << "Error: bad input => " << date << std::endl;
                continue;
            }
            if (!isValidValue(valueStr))
            {
                std::cout << "Error: not a positive number." << std::endl;
                continue;
            }
            value = atof(valueStr.c_str());
            if (value > 1000)
            {
                std::cout << "Error: too large a number." << std::endl;
                continue;
            }
            double rate = getExchangeRate(date);
            std::cout << date << " => " << value << " = " << value * rate << std::endl;
        }
        else
        {
            std::cout << "Error: bad input => " << line << std::endl;
        }
    }
}

/**
 * @brief Récupère le taux de change
 */
double BitcoinExchange::getExchangeRate(const std::string & date) const
{
    std::map<std::string, double>::const_iterator it = _exchangeRates.lower_bound(date);
    if (it == _exchangeRates.end() || it->first != date)
    {
        if (it == _exchangeRates.begin())
            return 0;
        --it;
    }
    return it->second;
}

/**
 * @brief Fonction membre pour vérifier la validité de la date
 */
bool BitcoinExchange::isValidDate(const std::string& date) const
{
    // Simple check for format YYYY-MM-DD
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        return false;
        
    // Extract year, month, day
    int year = atoi(date.substr(0, 4).c_str());
    int month = atoi(date.substr(5, 2).c_str());
    int day = atoi(date.substr(8, 2).c_str());

    // Check ranges
    if (month < 1 || month > 12)
        return false;
    if (day < 1 || day > 31)
        return false;

    // Basic checks for month days
    if (month == 2)
    { // February
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > 29 || (day == 29 && !isLeap))
            return false;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day > 30)
            return false;
    }

    return true;
}

/**
 * @brief Fonction membre pour vérifier la validité de la valeur
 */
bool BitcoinExchange::isValidValue(const std::string& value) const
{
    char* end;
    double val = strtod(value.c_str(), &end);
    return end != value.c_str() && *end == '\0' && val >= 0;
}
