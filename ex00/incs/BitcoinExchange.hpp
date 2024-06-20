/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 23:48:07 by raveriss          #+#    #+#             */
/*   Updated: 2024/06/21 00:09:14 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Directive pour éviter les inclusions multiples d'un fichier d'en-tête */
#pragma once


#include <map>

/* 
 * Inclure <string> pour utiliser std::string
 * nécessaire pour les méthodes print et printLargeContainer
 */
#include <string>

class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange & operator = (const BitcoinExchange & other);
		~BitcoinExchange();

		void loadDatabase(const std::string & filename);
		double getValueAt(const std::string & date, double amount) const;

	private:
		std::map<std::string, double> exchangeRates;
		bool isValidDate(const std::string & date) const;
		bool isLeapYear(int year) const;
		bool isDateValid(int year, int month, int day) const;
};

/* BitcoinExchange.hpp */
