/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:53:54 by raveriss          #+#    #+#             */
/*   Updated: 2024/06/22 00:14:09 by raveriss         ###   ########.fr       */
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
	/* Ouvre le fichier pour lire les taux de change */
	std::ifstream file(filename.c_str());

	/* Vérifie si le fichier s'est correctement ouvert, sinon lance une exception */
	if (!file)
		throw std::runtime_error("Error: could not open file.");

	/* Variables pour stocker les lignes du fichier, les dates, et les taux */
	std::string line, date;
	double rate;

	/* Permet de sauter l'en-tête */
	getline(file, line);

	/* Lit le fichier ligne par ligne */
	while (getline(file, line))
	{
		/* Lit chaque ligne pour extraire la date et le taux */
		std::stringstream ss(line);

		/* Stocke la date et le taux dans la base de données pour des recherches rapides */
		if (getline(ss, date, ',') && (ss >> rate))
			_exchangeRates[date] = rate;
	}
}

/**
 * @brief Traite l'entrée
 */
void BitcoinExchange::processInput(const std::string & filename)
{
	/* Ouvre le fichier pour lire les données d'entrée */
	std::ifstream file(filename.c_str());

	/* Vérifie si le fichier s'est correctement ouvert, sinon lance une exception */	
	if (!file)
		throw std::runtime_error("Error: could not open file.");
		
	/* Variables pour stocker les lignes du fichier, les dates, et les valeurs */
	std::string line, date, valueStr;
	double value;

	/* Permet de sauter l'en-tête */
	getline(file, line);

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
			
			/* Récupère le taux de change pour la date donnée */
			double rate = getExchangeRate(date);
			
			/* Affiche la date, la valeur et le montant converti selon le taux de change */
			std::cout << date << " => " << value << " = " << value * rate << std::endl;
		}
		else
		{
			/* Vérifie si la ligne est correctement formatée, sinon affiche une erreur */
			std::cout << "Error: bad input => " << line << std::endl;
		}
	}
}

/**
 * @brief Récupère le taux de change
 */
double BitcoinExchange::getExchangeRate(const std::string & date) const
{
	/* std::map::lower_bound() returns an iterator pointing to the first element in the container whose key is not considered to go before k */
	std::map<std::string, double>::const_iterator it = _exchangeRates.lower_bound(date);
	
	/* If the date is not found, the function returns an iterator to the next date */
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
	/* Vérifie si la taille de la date est de 10 caractères et si les caractères 4 et 7 sont des tirets */
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return false;

	/* Extraire l'année, le mois, le jour */
	int year = atoi(date.substr(0, 4).c_str());
	int month = atoi(date.substr(5, 2).c_str());
	int day = atoi(date.substr(8, 2).c_str());

	/* Vérifie si le mois est compris entre 1 et 12 */
	if (month < 1 || month > 12)
		return false;

	/* Vérifie si le jour est compris entre 1 et 31 */
	if (day < 1 || day > 31)
		return false;

	/* Vérifie si le mois est février */
	if (month == 2)
	{ 
		/* Variable booléenne isLeap indiquer si l'année est bissextile.
   		Une année est bissextile si elle est divisible par 4 mais pas par 100,
   		sauf si elle est également divisible par 400. */     
		bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		
		/* Vérifie si le jour est supérieur à 29 ou si le jour est égal à 29 et que l'année n'est pas bissextile */
		if (day > 29 || (day == 29 && !isLeap))
			return false;
	}
	/* Vérifie si le mois est avril, juin, septembre ou novembre */
	else if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		/* Vérifie si le jour est supérieur à 30 */
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
	/* Pointeur sur le caractère de fin */
	char* end;

	/* Convertit la chaîne en double */
	double val = strtod(value.c_str(), &end);

	/* Vérifie si la chaîne est vide ou si la conversion a échoué */
	return end != value.c_str() && *end == '\0' && val >= 0;
}
