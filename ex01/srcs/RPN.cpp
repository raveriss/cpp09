/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raveriss <raveriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:14:23 by raveriss          #+#    #+#             */
/*   Updated: 2024/07/04 23:27:51 by raveriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Include the RPN class */
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
: _stack(other._stack)
{}

/**
 * @brief Surcharge operator =
 */
RPN & RPN::operator = (const RPN & other)
{
	if (this != &other)
		_stack = other._stack;
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
double RPN::performOperation(const std::string & operation, double operand1, double operand2)
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
 * @brief Function to validate the expression
 */
void RPN::validateExpression(const std::string & expression)
{
    for (size_t i = 0; i < expression.size(); ++i)
    {
        char c = expression[i];
        if (!isdigit(c) && c != '.' && c != '+' && c != '-' && c != '*' && c != '/' && c != ' ')
            throw std::runtime_error("Error: Invalid character in expression. Only digits, spaces, and operators (+, -, *, /) are allowed.");
    }
}

/**
 * @brief Function to evaluate an expression
 */
double RPN::evaluate(const std::string & expression)
{
	validateExpression(expression);
	std::istringstream iss(expression);
	std::string token;

	while (iss >> token)
	{
        if (token.find(',') != std::string::npos)
            throw std::runtime_error("Error: Invalid character ',' in expression. Use '.' for decimal points.");	
		
		if (isdigit(token[0]))
		{
			std::stringstream ss(token);
			double number;
			ss >> number;
			_stack.push(number);
		}

		else if (isOperator(token))
		{
			if (_stack.size() < 2)
				throw std::runtime_error("Error: Not enough operands for operation");
			double operand2 = _stack.top();
			_stack.pop();
			double operand1 = _stack.top();
			_stack.pop();
			double result = performOperation(token, operand1, operand2);
			_stack.push(result);
		}

		else
			throw std::runtime_error("Error");
	}

	/* Check if there is only one operand left on the stack */
	if (_stack.size() != 1)
		throw std::runtime_error("Error: Too many operands left on the stack");

	return _stack.top();
}

/* RPN.cpp */
