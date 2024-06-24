/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:14:23 by raveriss          #+#    #+#             */
/*   Updated: 2024/06/24 18:14:24 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/RPN.hpp"

/**
 * @brief Construct default RPN
 */
RPN::RPN()
{}

/**
 * @brief Construct RPN by copy
 */
RPN::RPN(const RPN & other)
: stack(other.stack)
{}

/**
 * @brief Surcharge operator =
 */
RPN& RPN::operator=(const RPN & other)
{
    if (this != &other)
        stack = other.stack;
    return *this;
}

/**
 * @brief Destruct RPN
 */
RPN::~RPN()
{}

/**
 * @brief Function to check if a token is an operator
 */
bool RPN::isOperator(const std::string & token)
{
    return token == "+" || token == "-" || token == "*" || token == "/";
}

/**
 * @brief Function to perform an operation
 */
int RPN::performOperation(const std::string & operation, int operand1, int operand2)
{
    if (operation == "+")
        return operand1 + operand2;
    if (operation == "-")
        return operand1 - operand2;
    if (operation == "*")
        return operand1 * operand2;
    if (operation == "/")
    {
        if (operand2 == 0)
            throw std::runtime_error("Error: Division by zero");
        return operand1 / operand2;
    }
    throw std::runtime_error("Invalid operator");
}

/**
 * @brief Function to evaluate an expression
 */
int RPN::evaluate(const std::string & expression)
{
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token)
    {
        if (isdigit(token[0]))
        {
            std::stringstream ss(token);
            int number;
            ss >> number;
            stack.push(number);
        }
        else if (isOperator(token))
        {
            if (stack.size() < 2)
                throw std::runtime_error("Error: Not enough operands for operation");
            int operand2 = stack.top();
            stack.pop();
            int operand1 = stack.top();
            stack.pop();
            int result = performOperation(token, operand1, operand2);
            stack.push(result);
        }
        else
            throw std::runtime_error("Error: Invalid token '" + token + "'");
    }

    if (stack.size() != 1)
        throw std::runtime_error("Error: Too many operands left on the stack");

    return stack.top();
}

/* RPN.cpp */
