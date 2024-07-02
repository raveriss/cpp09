/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:53:13 by raveriss          #+#    #+#             */
/*   Updated: 2024/07/02 21:26:01 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/PmergeMe.hpp"

/**
 * @brief Default constructor
 */
PmergeMe::PmergeMe()
{}

/**
 * @brief Copy constructor
 */
PmergeMe::PmergeMe(const PmergeMe & other)
{
    (void)other;
}

/**
 * @brief Assignment operator
 */
PmergeMe & PmergeMe::operator = (const PmergeMe & other)
{
    if (this != &other)
    {}
    return *this;
}

/**
 * @brief Destructor
 */
PmergeMe::~PmergeMe()
{}

/* PmergeMe.cpp */
