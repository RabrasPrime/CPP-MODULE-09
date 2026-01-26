//
// Created by tjooris on 1/16/26.
//

#ifndef CPP_MODULE_09_BITCOINEXCHANGE_HPP
#define CPP_MODULE_09_BITCOINEXCHANGE_HPP

#define DATE_FORMAT "YYYY-MM-DD"
#define MAX_VALUE 1000.0
#define MIN_VALUE 0.0
#define DATA_FILE "data.csv"

#include <iostream>
#include <cstdlib>
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
		int	readFlag;
	public:
        BitcoinExchange();
        ~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange&	operator=(const BitcoinExchange& other);

        void				loadData(const std::string& filename);
        double				getExchangeRate(const std::string& date) const;
        static bool			isValidDate(const std::string& date);
	static int				isValidValue(const std::string& valueStr, double& value);

};


#endif //CPP_MODULE_09_BITCOINEXCHANGE_HPP