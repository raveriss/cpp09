/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:53:13 by raveriss          #+#    #+#             */
/*   Updated: 2024/07/02 20:20:05 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/PmergeMe.hpp"

PmergeMe::PmergeMe()
{}

PmergeMe::PmergeMe(const PmergeMe & other)
{
    (void)other;
}

PmergeMe & PmergeMe::operator = (const PmergeMe & other)
{
    if (this != &other)
    {}
    return *this;
}

PmergeMe::~PmergeMe()
{}

/* PmergeMe.cpp */
