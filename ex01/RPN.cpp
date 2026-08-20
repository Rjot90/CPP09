#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN &other) : _stack(other._stack) {}

RPN &RPN::operator=(const RPN &other) {
    if (this != &other)
        _stack = other._stack;
    return *this;
}

RPN::~RPN() {}

void RPN::applyOperator(char op) {
    if (_stack.size() < 2)
        throw std::runtime_error("Error");

    int b = _stack.top();
    _stack.pop();
    
    int a = _stack.top();
    _stack.pop();

    if (op == '/' && b == 0)
        throw std::runtime_error("Error");

    int result;
    switch (op) {
    case '+':
        result = a + b;
        break;
    case '-':
        result = a - b;
        break;
    case '*':
        result = a * b;
        break;
    case '/':
        result = a / b;
        break;
    }
    _stack.push(result);
}

int RPN::evaluate(const std::string &expression) {
    while (!_stack.empty())
        _stack.pop();

    for (size_t i = 0; i < expression.size(); i++) {
        
        char c = expression[i];
        if (c == ' ')
            continue;
        if (std::isdigit(c)) {
            if (i + 1 < expression.size() && std::isdigit(expression[i + 1]))
                throw std::runtime_error("Error");
            _stack.push(c - '0');
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/')
            applyOperator(c);
        else
            throw std::runtime_error("Error");
    }

    if (_stack.size() != 1)
        throw std::runtime_error("Error");
    return _stack.top();
}
