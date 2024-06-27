/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:54:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/06/27 18:01:00 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Inclusion de la classe BitcoinExchange */
#include "BitcoinExchange.hpp"

/**
 * @brief Fonction main
 * @param argc le nombre d'arguments
 * @param argv les arguments
 * @return 0 si tout se passe bien, 1 sinon
 */
int main(int argc, char* argv[])
{
    /* Vérification si le nombre d'arguments est exactement 2 */
    if (argc != EXPECTED_ARGC)
    {
        std::cerr << "Usage: ./btc input.txt" << std::endl;
        return RETURN_FAILURE;
    }

    /* Bloc try pour gérer les exceptions */
    try
    {
        /* Création de l'instance exchange de la classe BitcoinExchange */
        BitcoinExchange exchange;
        
        /* Chargement de la base de données data.csv */
        exchange.loadDatabase("data.csv");

        /* Traitement de l'entrée input.txt */
        exchange.processInput(argv[1]);
    }
    
    /* Gestion des exceptions */
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return RETURN_FAILURE;
    }

    return RETURN_SUCCESS;
}

/* main.cpp */
