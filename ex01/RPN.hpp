#pragma once
#include <iostream>
#include <string>
#include <stack>
#include <stdexcept>

class RPN {
    private:
        std::stack<int> _stack;

        void applyOperator(char op);

    public:
        RPN();
        RPN(const RPN &other);
        RPN &operator=(const RPN &other);
        ~RPN();

        int evaluate(const std::string &expression);
};