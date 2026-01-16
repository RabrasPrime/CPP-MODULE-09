//
// Created by tjooris on 1/16/26.
//

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
    loadData("data.csv");
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
    this->exchangeRates = other.exchangeRates;
}

BitcoinExchange&	BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
    {
        this->exchangeRates = other.exchangeRates;
    }
    return *this;
}

