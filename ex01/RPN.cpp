#include "RPN.hpp"
#include <iostream>
#include <stack>
#include <list>
#include <cctype>      // pour isdigit
#include <stdexcept>   // pour exception

RPN::RPN()
{
}

RPN::RPN(const RPN &other)
{
    (void)other;
}

RPN &RPN::operator=(const RPN &other)
{
    (void)other;
    return *this;
}

RPN::~RPN()
{
}

int RPN::evaluate(const std::string &expression) const
{
    std::stack<int, std::list<int> > st;

    for (size_t i = 0; i < expression.size(); ++i)
    {
        char c = expression[i];

        if (c == ' ')
            continue;

        if (std::isdigit(c))
        {
            if (i + 1 < expression.size() && std::isdigit(expression[i + 1]))
                throw std::runtime_error("Error");
            int value = c - '0';
            st.push(value);
            continue;
        }

        if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            if (st.size() < 2)
                throw std::runtime_error("Error");

            int b = st.top();
            st.pop();
            int a = st.top();
            st.pop();

            int result;

            switch (c)
            {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/':
                    if (b == 0)
                        throw (std::runtime_error("Error"));
                    result = a / b;
                    break;
            }
            st.push(result);
            continue;
        }

        throw (std::runtime_error("Error"));

    }

    if (st.size() != 1)
        throw (std::runtime_error("Error"));

    return (st.top());
}
