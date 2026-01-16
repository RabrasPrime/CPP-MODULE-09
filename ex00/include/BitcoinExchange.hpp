//
// Created by tjooris on 1/16/26.
//

#ifndef CPP_MODULE_09_BITCOINEXCHANGE_HPP
#define CPP_MODULE_09_BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <string>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <limits>

class BitcoinExchange
{
	private:
        std::map<std::string, double> exchangeRates;
        bool isValidDate(const std::string& date) const;
        bool isLeapYear(int year) const;
        bool isValidValue(const std::string& valueStr, double& value) const;
	public:
		BitcoinExchange();
        ~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);


};


#endif //CPP_MODULE_09_BITCOINEXCHANGE_HPP