//
// Created by tjooris on 1/16/26.
//

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
    loadData(DATA_FILE);
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

void	BitcoinExchange::loadData(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
        throw std::runtime_error("Could not open data file.");

    std::string line;
    bool firstLine = true;

    while (std::getline(file, line))
    {
        if (firstLine)
        {
            firstLine = false;
            if (line != "date,exchange_rate")
                throw std::runtime_error("Invalid header in data file. Expected: date,exchange_rate");
            continue;
        }

        std::istringstream ss(line);
        std::string date;
        std::string rateStr;

        if (!std::getline(ss, date, ',') || !std::getline(ss, rateStr))
            throw std::runtime_error("Invalid line format in data file.");

        date.erase(0, date.find_first_not_of(" \t"));
        date.erase(date.find_last_not_of(" \t") + 1);
        rateStr.erase(0, rateStr.find_first_not_of(" \t"));
        rateStr.erase(rateStr.find_last_not_of(" \t") + 1);

        if (!isValidDate(date))
            throw std::runtime_error("Invalid date format in data file: " + date);

        char* end;
        double rate = std::strtod(rateStr.c_str(), &end);

        if (end == rateStr.c_str() || *end != '\0')
            throw std::runtime_error("Invalid exchange rate in data file: " + rateStr);

        if (rate < 0)
            throw std::runtime_error("Negative exchange rate in data file: " + rateStr);

        exchangeRates[date] = rate;
    }
    file.close();
}

double	BitcoinExchange::getExchangeRate(const std::string& date) const
{
    std::map<std::string, double>::const_iterator it = exchangeRates.find(date);
    if (it != exchangeRates.end())
        return it->second;

    it = exchangeRates.lower_bound(date);
    if (it == exchangeRates.begin())
        throw std::runtime_error("No exchange rate available for the given date or any previous date.");

    --it;
    return it->second;
}

bool	BitcoinExchange::isValidDate(const std::string& date)
{
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return false;

    if (month == 2)
    {
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > (isLeapYear ? 29 : 28))
            return false;
    }

    return true;
}

int	BitcoinExchange::isValidValue(const std::string& valueStr, double& value)
{
    char* end;
    value = std::strtod(valueStr.c_str(), &end);

    if (end == valueStr.c_str() || *end != '\0')
        return 0;

    if (value < 0)
        return -1;

    if (value > MAX_VALUE)
        return -2;

    return 1;
}