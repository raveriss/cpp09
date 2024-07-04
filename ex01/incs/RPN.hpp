/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:45:49 by raveriss          #+#    #+#             */
/*   Updated: 2024/07/04 19:01:16 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Define macro to avoid multiple inclusions */
#pragma once

/* Inclusion de la bibliothèque standard pour std::cout */
#include <iostream>

/* Include the stack container files */
#include <stack>

/* Inclusion de la bibliothèque standard pour std::sstream */
#include <sstream>

/* Inclusion de la bibliothèque standard pour std::string */
#include <string>

/* Include the standard library for std::floor */
#include <cmath>

/* Include the standard library for std::setprecision */
#include <iomanip>

/* Define values */
#define RETURN_SUCCESS 0
#define RETURN_FAILURE 1
#define EXPECTED_ARGC 2

/**
 * @brief Class RPN
 */
class RPN
{
    public:
    
        /* Constructeur par défaut */
        RPN();

        /* Constructeur par copie */
        RPN(const RPN & other);

        /* Opérateur d'affectation */
        RPN & operator = (const RPN & other);

        /* Destructeur */
        ~RPN();

        /* Fonction pour évaluer l'expression */
        double evaluate(const std::string & expression);

    private:

        /* Pile d'entiers */
        std::stack<double> _stack;

        /* Function to check if a token is an operator */
        bool isOperator(const std::string & token);
        
        /* Function to perform an operation */
        double performOperation(const std::string & operation, double operand1, double operand2);

        /* Function to validate the expression */
        void validateExpression(const std::string & expression);

};

/* RPN_HPP */
