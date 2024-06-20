#include "../incs/BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

#define GREY        "\033[0;30m"
#define RED         "\033[0;31m"
#define GREEN       "\033[0;32m"
#define YELLOW      "\033[0;33m"
#define BLUE        "\033[0;34m"
#define MAGENTA     "\033[0;35m"
#define CYAN        "\033[0;36m"
#define WHITE       "\033[0;37m"
#define BRIGHT_GREY    "\033[1;30m"
#define BRIGHT_RED     "\033[1;31m"
#define BRIGHT_GREEN   "\033[1;32m"
#define BRIGHT_YELLOW  "\033[1;33m"
#define BRIGHT_BLUE    "\033[1;34m"
#define BRIGHT_MAGENTA "\033[1;35m"
#define BRIGHT_CYAN    "\033[1;36m"
#define BRIGHT_WHITE   "\033[1;37m"
#define BLACK_BG       "\033[40m"
#define RED_BG         "\033[41m"
#define GREEN_BG       "\033[42m"
#define YELLOW_BG      "\033[43m"
#define BLUE_BG        "\033[44m"
#define MAGENTA_BG     "\033[45m"
#define CYAN_BG        "\033[46m"
#define WHITE_BG       "\033[47m"
#define BOLD           "\033[1m"
#define UNDERLINE      "\033[4m"
#define RESET          "\033[0m"
#define NC             RESET
#define RETURN_SUCCESS 0
#define RETURN_FAILURE 1

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return RETURN_FAILURE;
    }

    BitcoinExchange exchange;
    exchange.loadDatabase(); // Chargement manuel des taux de change

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error: could not open file " << argv[1] << std::endl;
        return RETURN_FAILURE;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        if (line == "date | value") continue;

        std::istringstream iss(line);
        std::string date;
        std::string valueStr;

        if (std::getline(iss, date, '|') && std::getline(iss, valueStr)) {
            date = date.substr(0, date.find_last_not_of(" ") + 1);
            valueStr = valueStr.substr(valueStr.find_first_not_of(" "));
            std::istringstream valueStream(valueStr);
            double value;

            if (!(valueStream >> value)) {
                std::cerr << "Error: bad input => " << line << std::endl;
                continue;
            }
            try {
                double result = exchange.getValueAt(date, value);
                std::cout << date << " => " << value << " = " << result << std::endl;
            } catch (const std::invalid_argument&) {
                std::cerr << "Error: bad input => " << line << std::endl;
            } catch (const std::domain_error&) {
                std::cerr << "Error: not a positive number." << std::endl;
            } catch (const std::out_of_range&) {
                std::cerr << "Error: too large a number." << std::endl;
            } catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
        } else {
            std::cerr << "Error: bad input => " << line << std::endl;
        }
    }

    inputFile.close();
    return RETURN_SUCCESS;
}
