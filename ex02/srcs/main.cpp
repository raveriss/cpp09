/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:29:15 by raveriss          #+#    #+#             */
/*   Updated: 2024/06/29 21:22:03 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Inclusion of the PmergeMe header file */
#include "../incs/PmergeMe.hpp"


long long int getSum_On(int n)
{
    long long int sum = 0; // Déclaration de sum en dehors de la boucle
    for (int number = 1; number <= n; ++number)
    {
        sum += number;
    }
    return sum;
}
    
long long int getSum_O1(int n)
{
    return n * (n + 1) / 2;
}

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
        std::cerr << "Usage: " << argv[0] << " num1 num2 num3 ... numN or " << argv[0] << " tester" << std::endl;
        return RETURN_FAILURE;
    }

    // else if (argc == ARG_ONE && strcmp(argv[FIRST_ARGUMENT], TEST_ARG) == STRING_COMPARE_SUCCESS)
    // {
    //     std::cout << CYAN << "/* -'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-',-'-,-'- */" << NC << std::endl;
    //     std::cout << CYAN << "/*                                 OPTIONNEL                                  */" << NC << std::endl;
    //     std::cout << CYAN << "/* -'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-',-'-,-'- */\n" << NC << std::endl;

    //     std::clock_t start_On = std::clock();
    //     getSum_On(10000000);
    //     std::clock_t end_On = std::clock();
    //     double duration_On = 1000000.0 * (end_On - start_On) / CLOCKS_PER_SEC;
    
    //     std::clock_t start_O1 = std::clock();
    //     getSum_O1(5);
    //     std::clock_t end_O1 = std::clock();
    //     double duration_O1 = 1000000.0 * (end_O1 - start_O1) / CLOCKS_PER_SEC;

    //     std::cout << "Time to process a range of " << 5 << " n with getSum_On " 
    //           << duration_On << " us" << std::endl;
    //     std::cout << "Time to process a range of " << 5 << " n with getSum_O1 " 
    //         << duration_O1 << " us" << std::endl;
    // }
    
    else
    {
        std::vector<int> data;
        std::deque<int> deq;

        for (int i = 1; i < argc; ++i)
        {
            if (!isPositiveInteger(argv[i]))
            {
                std::cerr << "Error: Invalid input '" << argv[i] << "'. All inputs must be positive integers." << std::endl;
                return RETURN_FAILURE;
            }
            int num = std::atoi(argv[i]);
            data.push_back(num);
            deq.push_back(num);
        }
        std::cout << CYAN << "/*   -'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-',-'   */\n" << NC;
        std::cout << CYAN << "/*                                  VECTOR                                   */\n" << NC;
        std::cout << CYAN << "/*   -'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-',-'   */\n" << NC;

        std::cout << BRIGHT_BLUE << "Before" << NC << " : ";
        for (std::vector<int>::iterator it = data.begin(); it != data.end(); ++it)
        {
            std::cout << *it << " ";
        }

        if (data.size() > 26)
            std::cout << std::endl;

        /* Measure time for std::vector */
        std::clock_t startVector = std::clock();
        mergeInsertSort(data);
        std::clock_t endVector = std::clock();
        double durationVector = 1000000.0 * (endVector - startVector) / CLOCKS_PER_SEC;

        /* Measure time for std::deque */
        std::cout << CYAN <<  "\n/*   -'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-',-'   */\n" << NC;
        std::cout << CYAN << "/*                                   DEQUE                                   */\n" << NC;
        std::cout << CYAN << "/*   -'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-',-'   */\n" << NC;
        
        std::cout << BRIGHT_BLUE << "Before" << NC << " : ";
        for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); ++it)
        {
            std::cout << *it << " ";
        }

        if (deq.size() > 26)
            std::cout << std::endl;
        std::clock_t startDeque = std::clock();
        mergeInsertSort(deq);
        std::clock_t endDeque = std::clock();
        double durationDeque = 1000000.0 * (endDeque - startDeque) / CLOCKS_PER_SEC;

        std::cout << std::endl;

        /* Measure time for std::deque */
        std::cout << CYAN <<  "/*   -'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-',-'   */\n" << NC;
        std::cout << CYAN << "/*                                  RESULTAT                                 */\n" << NC;
        std::cout << CYAN << "/*   -'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-',-'   */\n" << NC;

        const char* vectorColor = (durationVector <= durationDeque) ? GREEN_BG : RED_BG;
        const char* dequeColor = (durationDeque <= durationVector) ? GREEN_BG : RED_BG;

        std::cout << BRIGHT_MAGENTA << "Time to process a range of " << data.size() << " elements with std::\n" << vectorColor << " vector " 
                << NC << ": " << durationVector << " us" << std::endl;
        std::cout << dequeColor << " deque " << NC << ": " << durationDeque << " us" << std::endl << std::endl;
    }
    return RETURN_SUCCESS;
}

/* main.cpp */
