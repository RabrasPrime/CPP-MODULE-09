//
// Created by tjooris on 1/28/26.
//

#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>  // Pour std::sort
#include <limits>
#include <cerrno>
#include <sys/time.h>

bool isValidNumber(const std::string& str, int& value)
{
    if (str.empty())
        return false;

    for (size_t i = 0; i < str.length(); ++i)
    {
        if (!std::isdigit(str[i]))
            return false;
    }

    errno = 0;
    char* endptr;
    long val = std::strtol(str.c_str(), &endptr, 10);

    if (errno == ERANGE || val > std::numeric_limits<int>::max() || val < 0)
        return false;

    if (*endptr != '\0')
        return false;

    value = static_cast<int>(val);
    return true;
}

double getTime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Error wrong number of arguments" << std::endl;
        return 1;
    }

    try
    {
        std::vector<int, Allocator> vec;
        std::deque<int, Allocator> deq;
        std::vector<int> vecStdSort;

        for (int i = 1; i < argc; ++i)
        {
            int value;
            if (!isValidNumber(argv[i], value))
            {
                std::cerr << "Error wrong type number" << std::endl;
                return 1;
            }
            vec.push_back(value);
            deq.push_back(value);
            vecStdSort.push_back(value);
        }

        std::cout << "Before: ";
        for (size_t i = 0; i < vec.size(); ++i)
        {
            std::cout << vec[i];
            if (i < vec.size() - 1)
                std::cout << " ";
        }
        std::cout << std::endl;

        std::sort(vecStdSort.begin(), vecStdSort.end());

        double startVec = getTime();
        mergeInsertSort<std::vector>(vec);
        double endVec = getTime();
        double timeVec = (endVec - startVec) * 1000000;

        std::cout << "After: ";
        for (size_t i = 0; i < vec.size(); ++i)
        {
            std::cout << vec[i];
            if (i < vec.size() - 1)
                std::cout << " ";
        }
        std::cout << std::endl;

        double startDeq = getTime();
        mergeInsertSort<std::deque>(deq);
        double endDeq = getTime();
        double timeDeq = (endDeq - startDeq) * 1000000;

        std::cout << "Time to process a range of " << vec.size()
                  << " elements with std::vector : " << timeVec / 100 << " us" << std::endl;
        std::cout << "Time to process a range of " << deq.size()
                  << " elements with std::deque : " << timeDeq << " us" << std::endl;

        bool identical = true;
        if (vec.size() != deq.size())
            identical = false;
        else
        {
            for (size_t i = 0; i < vec.size(); ++i)
            {
                if (vec[i] != deq[i])
                {
                    identical = false;
                    break;
                }
            }
        }

        if (!identical)
        {
            std::cerr << "Error: vector and deque results differ!" << std::endl;
            return 1;
        }

        bool correctSort = true;
        for (size_t i = 0; i < vec.size(); ++i)
        {
            if (vec[i] != vecStdSort[i])
            {
                correctSort = false;
                break;
            }
        }

        if (!correctSort)
        {
            std::cerr << "Error: sort is incorrect compared to std::sort!" << std::endl;
            std::cerr << "Expected (std::sort): ";
            for (size_t i = 0; i < vecStdSort.size(); ++i)
            {
                std::cout << vecStdSort[i];
                if (i < vecStdSort.size() - 1)
                    std::cout << " ";
            }
            std::cout << std::endl;
            return 1;
        }

        std::cout << "Success: results are identical and correctly sorted." << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    return 0;
}