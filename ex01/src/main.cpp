//
// Created by tjooris on 1/27/26.
//

#include "RPN.hpp"

int    main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "Error: invalid number of arguments." << std::endl;
        return 1;
    }

    try
    {
        int result = evaluateRPN(argv[1]);
        std::cout << result << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}