/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:46:19 by raveriss          #+#    #+#             */
/*   Updated: 2024/06/24 18:11:24 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/RPN.hpp"

/***
 * @brief Main function
 */
int main(int argc, char* argv[])
{
    if (argc != EXPECTED_ARGC)
    {
        std::cerr << "Usage: " << argv[0] << " <expression>" << std::endl;
        return RETURN_FAILURE;
    }

    try
    {
        RPN rpn;
        int result = rpn.evaluate(argv[1]);
        std::cout << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return RETURN_FAILURE;
    }

    return RETURN_SUCCESS;
}

/* main.cpp */
