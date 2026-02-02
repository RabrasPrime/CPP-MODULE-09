//
// Created by tjooris on 1/16/26.
//

#include "BitcoinExchange.hpp"

int    main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "Error: could not open file." << std::endl;
        return 1;
    }

    try
    {
        BitcoinExchange btcExchange;

        std::ifstream inputFile(argv[1]);
        if (!inputFile.is_open())
        {
            std::cout << "Error: could not open file." << std::endl;
            return 1;
        }

        std::string line;
        bool firstLine = true;

        while (std::getline(inputFile, line))
        {
            if (firstLine)
            {
                firstLine = false;
				if (line != "date | value")
					return std::cout << "Error: bad input => " << line << std::endl, 1;
                continue;
            }

            std::istringstream ss(line);
            std::string date;
            std::string valueStr;

            if (std::getline(ss, date, '|') && std::getline(ss, valueStr))
            {
                date.erase(0, date.find_first_not_of(" \t"));
                date.erase(date.find_last_not_of(" \t") + 1);
                valueStr.erase(0, valueStr.find_first_not_of(" \t"));
                valueStr.erase(valueStr.find_last_not_of(" \t") + 1);

                if (!BitcoinExchange::isValidDate(date))
                {
                    std::cout << "Error: bad input => " << date << std::endl;
                    continue;
                }
                double value;
                int validationResult = BitcoinExchange::isValidValue(valueStr, value);

                if (validationResult == -1)
                {
                    std::cout << "Error: not a positive number." << std::endl;
                    continue;
                }
                else if (validationResult == -2)
                {
                    std::cout << "Error: too large a number." << std::endl;
                    continue;
                }
                else if (validationResult == 0)
                {
                    std::cout << "Error: bad input => " << valueStr << std::endl;
                    continue;
                }

                try
                {
                    double rate = btcExchange.getExchangeRate(date);
                    double result = rate * value;
                    std::cout << date << " => " << value << " = " << result << std::endl;
                }
                catch (const std::exception& e)
                {
                    std::cout << "Error: " << e.what() << std::endl;
                }
            }
            else
            {
                std::cout << "Error: bad input => " << line << std::endl;
            }
        }

        inputFile.close();
    }
    catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}