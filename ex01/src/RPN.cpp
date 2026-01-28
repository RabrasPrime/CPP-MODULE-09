//
// Created by tjooris on 1/27/26.
//

#include "RPN.hpp"

static int	isOperator(const std::string& token)
{
    return (token == "+" || token == "-" || token == "*" || token == "/");
}

static int	isOperand(const std::string& token)
{
    if (token.empty())
        return 0;
    for (size_t i = 0; i < token.length(); ++i)
    {
        if (!isdigit(token[i]))
            return 0;
    }
    return 1;
}

int evaluateRPN(const std::string& expression)
{
	std::stack<int> stk;
	std::istringstream ss(expression);
	std::string token;

	while (ss >> token)
    {
        if (isOperand(token))
        {
            stk.push(std::atoi(token.c_str()));
        }
        else if (isOperator(token))
        {
            if (stk.size() < 2)
                throw std::runtime_error("Error: insufficient operands.");

            int right = stk.top(); stk.pop();
            int left = stk.top(); stk.pop();

            if (token == "+")
                stk.push(left + right);
            else if (token == "-")
                stk.push(left - right);
            else if (token == "*")
                stk.push(left * right);
            else if (token == "/")
            {
                if (right == 0)
                    throw std::runtime_error("Error: division by zero.");
                stk.push(left / right);
            }
        }
        else
        {
            throw std::runtime_error("Error: invalid token '" + token + "'.");
        }
    }
    if (stk.size() != 1)
        throw std::runtime_error("Error: invalid RPN expression.");
    return stk.top();
}
