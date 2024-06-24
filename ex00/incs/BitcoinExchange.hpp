/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:53:59 by raveriss          #+#    #+#             */
/*   Updated: 2024/06/24 02:02:46 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Définition de la macro pour éviter les inclusions multiples */
#pragma once

/* Inclusion de la bibliothèque standard pour std::map */
#include <map>

/* Inclusion de la bibliothèque standard pour std::string */
#include <string>

/* Inclusion de la bibliothèque standard pour std::cerr */
#include <iostream>

/* Inclusion de la bibliothèque standard pour std::ifstream */
#include <fstream>

/* Inclusion de la bibliothèque standard pour std::sstream */
#include <sstream>

/* Inclusion de la bibliothèque standard pour std::runtime_error */
#include <stdexcept>

/* Inclusion de la bibliothèque standard pour std::atof */
#include <cstdlib>

/* Inclusion de la bibliothèque standard pour std::cout */
#include <iostream>

/* Define values */
#define RETURN_SUCCESS 0
#define RETURN_FAILURE 1
#define EXPECTED_ARGC 2

/* Définition des constantes pour la validation de la date */
#define DATE_LENGTH 10
#define YEAR_POSITION 4
#define MONTH_POSITION 7
#define MIN_YEAR_DIGITS 0
#define MAX_YEAR_DIGITS 4
#define MIN_MONTH_DIGITS 5
#define MAX_MONTH_DIGITS 7
#define MIN_DAY_DIGITS 8
#define MAX_DAY_DIGITS 10
#define MIN_MONTH 1
#define MAX_MONTH 12
#define MIN_DAY 1
#define MAX_DAY 31

/* Définition des constantes pour les longueurs de sous-chaînes */
#define YEAR_LENGTH 4
#define MONTH_LENGTH 2
#define DAY_LENGTH 2

/* Définition des constantes pour les mois */
#define FEBRUARY 2
#define APRIL 4
#define JUNE 6
#define SEPTEMBER 9
#define NOVEMBER 11

/**
 * @brief Classe BitcoinExchange
 */
class BitcoinExchange
{
    public:

		/* Constructeur par défaut */
        BitcoinExchange();

		/* Constructeur par copie */
        BitcoinExchange(const BitcoinExchange & other);

		/* Opérateur d'affectation */
        BitcoinExchange & operator = (const BitcoinExchange & other);

		/* Destructeur */
        ~BitcoinExchange();

		/* Charge la base de données */
        void loadDatabase(const std::string & filename);

		/* Traite l'entrée */
        void processInput(const std::string & filename);

		/* Récupère le taux de change */
        double getExchangeRate(const std::string & date) const;

    private:

		/* containers pour stocker les taux de change */
        std::map<std::string, double> _exchangeRates;

		/* Fonction membre pour vérifier la validité de la date */
        bool isValidDate(const std::string & date) const;

		/* Fonction membre pour vérifier la validité de la valeur */
        bool isValidValue(const std::string & value) const;
};

/* BitcoinExchange.hpp */
