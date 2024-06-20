#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define NC "\033[0m" // No Color

/* Macro pour vérifier les résultats de test et afficher les messages appropriés */
#define ASSERT_TEST(expression, message) \
    if (expression) { std::cout << GREEN "[TEST PASSED] " NC << message << std::endl; } \
    else { std::cout << RED "[TEST FAILED] " NC << message << std::endl; }

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;

        return 1;
    }

    BitcoinExchange exchange;
    try
    {
        exchange.loadDatabase("database.txt"); // Assurez-vous que ce fichier existe dans le bon répertoire
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;

        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;

        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line))
    {
        if (line == "date | value") continue; // Ignore the header line

        std::istringstream iss(line);
        std::string date;
        std::string valueStr;

        if (std::getline(iss, date, '|') && std::getline(iss, valueStr))
        {
            date = date.substr(0, date.find_last_not_of(" ") + 1); // Trim spaces
            valueStr = valueStr.substr(valueStr.find_first_not_of(" ")); // Trim spaces
            std::istringstream valueStream(valueStr);
            double value;

            if (!(valueStream >> value))
            {
                std::cerr << "Error: bad input => " << line << std::endl;
                continue;
            }
            try
            {
                double result = exchange.getValueAt(date, value);
                std::cout << date << " => " << value << " = " << result << std::endl;
            }
            catch (const std::invalid_argument&)
            {
                std::cerr << "Error: bad input => " << line << std::endl;
            }
            catch (const std::out_of_range&)
            {
                std::cerr << "Error: value out of range." << std::endl;
            }
            catch (const std::exception& e)
            {
                std::cerr << e.what() << std::endl;
            }
        }
        else
        {
            std::cerr << "Error: bad input => " << line << std::endl;
        }
    }
    inputFile.close();
    return 0;
}
