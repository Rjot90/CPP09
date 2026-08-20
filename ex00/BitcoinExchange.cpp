#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::loadDatabase(const std::string &filename) {

    std::ifstream file(filename.c_str());
    if (!file.is_open())
        throw std::runtime_error("Failed to open data file");

    std::string line;
    std::getline(file, line); //Skip first line

    while (std::getline(file, line)) {
        if (line.empty())
            continue;
        size_t comma = line.find(",");
        if (comma == std::string::npos)
            continue;
        std::string date = line.substr(0, comma);
        std::string val = line.substr(comma + 1);
        float rate = std::strtof(val.c_str(), NULL);
        _db[date] = rate;
    }
}

void BitcoinExchange::processInput(const std::string &filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open())
        throw std::runtime_error("Error: could not open input file.");

    std::string line;
    std::getline(file, line); // Skip first line

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        // Check " | "
        std::size_t sep = line.find(" | ");
        if (sep == std::string::npos) {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::string date = line.substr(0, sep);
        std::string valStr = line.substr(sep + 3); // +3 for " | "

        if (!isValidDate(date)) {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }

        float value;
        if (!isValidValue(valStr, value)) 
            continue;

        float rate;
        try {
            rate = getRateForDate(date);

        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
            continue;
        }
        std::cout << date << " => " << value << " = " << value * rate << std::endl;
    }
}

bool BitcoinExchange::isValidDate(const std::string& date) {
    
    int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    if (date.size() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) 
            continue;
        if (!std::isdigit(date[i]))
            return false;
    }

    int year  = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day   = std::atoi(date.substr(8, 2).c_str());
    bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

    if (month < 1 || month > 12)
        return false;
    if (day < 1 || day > 31)
        return false;

    if (leap)
        daysInMonth[1] = 29;
    if (day > daysInMonth[month - 1])
        return false;
    return true;
}

bool BitcoinExchange::isValidValue(const std::string &valStr, float &out) {

    if (valStr.empty()) {
        std::cerr << "Error: bad input." << std::endl;
        return false;
    }

    char *endptr;
    float value = std::strtof(valStr.c_str(), &endptr);

    if (*endptr != '\0') {
        std::cerr << "Error: bad input." << std::endl;
        return false;
    }

    if (value < 0) {
        std::cerr << "Error: not a positive number." << std::endl;
        return false;
    }

    if (value > 1000) {
        std::cerr << "Error: too large a number." << std::endl;
        return false;
    }

    out = value;
    return true;
}

float BitcoinExchange::getRateForDate(const std::string &date)
{
    std::map<std::string, float>::iterator it = _db.lower_bound(date);

    if (it == _db.end() || it->first != date) {
        if (it == _db.begin()) {
            throw std::runtime_error("Error: bad input => " + date);
        }
        --it;
    }
    return it->second;
}