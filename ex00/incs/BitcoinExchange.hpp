/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 23:48:07 by raveriss          #+#    #+#             */
/*   Updated: 2024/06/21 00:20:04 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Directive pour éviter les inclusions multiples d'un fichier d'en-tête */
#pragma once

/* 
 * Inclure <map> pour utiliser std::map
 * nécessaire pour la déclaration du conteneur exchangeRates
 */
#include <map>

/* 
 * Inclure <string> pour utiliser std::string
 * nécessaire pour les méthodes print et printLargeContainer
 */
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

		/* Surcharge de l'opérateur = */
		BitcoinExchange & operator = (const BitcoinExchange & other);

		/* Destructeur */
		~BitcoinExchange();

		/* Méthode pour charger la base de données */
		void loadDatabase(const std::string & filename);

		/* Méthode pour afficher les taux de change */
		double getValueAt(const std::string & date, double amount) const;

	private:
		
		/* Déclaration d'un conteneur de type std::map */
		std::map<std::string, double> exchangeRates;

		/* Méthode pour vérifier si une date est valide */
		bool isValidDate(const std::string & date) const;

		/* Méthode pour vérifier si une année est bissextile */
		bool isLeapYear(int year) const;

		/* Méthode pour vérifier si une date est valide */
		bool isDateValid(int year, int month, int day) const;
};

/* BitcoinExchange.hpp */
