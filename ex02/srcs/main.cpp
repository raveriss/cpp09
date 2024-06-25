/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:29:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/06/25 15:56:11 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <ctime>
#include <cstdlib>

/**
 * @brief Check if a string is a positive integer
 */
bool isPositiveInteger(const std::string& str)
{
    for (size_t i = 0; i < str.length(); ++i)
    {
        if (!isdigit(str[i]))
            return false;
    }
    return !str.empty();
}

/**
 * @brief Main function
 */
int main(int argc, char* argv[])
{
    if (argc < EXPECTED_ARGC)
    {
        std::cerr << "Usage: " << argv[0] << " num1 num2 num3 ... numN" << std::endl;
        return RETURN_FAILURE;
    }

    std::vector<int> data;
    for (int i = 1; i < argc; ++i)
    {
        if (!isPositiveInteger(argv[i]))
        {
            std::cerr << "Error: Invalid input '" << argv[i] << "'. All inputs must be positive integers." << std::endl;
            return RETURN_FAILURE;
        }
        data.push_back(std::atoi(argv[i]));
    }

    std::cout << "Before: ";
    for (std::vector<int>::iterator it = data.begin(); it != data.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    /* Measure time for std::vector */
    std::clock_t startVector = std::clock();
    mergeInsertSort(data);
    std::clock_t endVector = std::clock();
    double durationVector = 1000000.0 * (endVector - startVector) / CLOCKS_PER_SEC;

    /* Measure time for std::deque */
    std::deque<int> deq(data.begin(), data.end());
    std::clock_t startDeque = std::clock();
    mergeInsertSort(deq);
    std::clock_t endDeque = std::clock();
    double durationDeque = 1000000.0 * (endDeque - startDeque) / CLOCKS_PER_SEC;

    std::cout << "After: ";
    for (std::vector<int>::iterator it = data.begin(); it != data.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Time to process a range of " << data.size() << " elements with std::vector: " 
              << durationVector << " us" << std::endl;
    std::cout << "Time to process a range of " << data.size() << " elements with std::deque: " 
              << durationDeque << " us" << std::endl;

    return RETURN_SUCCESS;
}
