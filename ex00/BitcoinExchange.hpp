#pragma once
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>

class BitcoinExchange {
    private:
        std::map<std::string, float> _db;

        bool isValidDate(const std::string& date);
        bool isValidValue(const std::string& val, float& out);
        float getRateForDate(const std::string& date);
    public:
        BitcoinExchange();
        ~BitcoinExchange();

        void loadDatabase(const std::string &filename);
        void processInput(const std::string &filename);

};
