/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 01:10:40 by raveriss          #+#    #+#             */
/*   Updated: 2024/06/27 22:15:43 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Définition de la macro pour éviter les inclusions multiples */
#pragma once

/* Inclusion de la bibliothèque standard pour std::vector */
#include <vector>

/* Inclusion de la bibliothèque standard pour std::deque */
#include <deque>

/* Include the standard library for std::cout */
#include <iostream>

/* Include the standard library for std::deque */
#include <deque>

/* Include the standard library for clock_t */
#include <ctime>

/* Include the standard library for std::atoi */
#include <cstdlib>

/* Define values */
#define RETURN_SUCCESS 0
#define RETURN_FAILURE 1
#define EXPECTED_ARGC 2

/**
 * @brief Fusionne deux moitiés d'un conteneur
 */
template <typename T>
void mergeInsertSort(T &container);

#include "../srcs/PmergeMe.tpp"

/* PMERGEME_HPP */
