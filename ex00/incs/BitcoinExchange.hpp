/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:53:59 by raveriss          #+#    #+#             */
/*   Updated: 2024/06/24 01:44:54 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Définition de la macro pour éviter les inclusions multiples */
#pragma once

/* Inclusion de la bibliothèque standard pour std::map */
#include <map>

/* Inclusion de la bibliothèque standard pour std::string */
#include <string>

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
