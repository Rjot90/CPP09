#include "BitcoinExchange.hpp"
int main(int ac, char **av) {
    try {
        if (ac != 2) {
            std::cerr << "Error: Not enough arguments." << std::endl
            << "Usage: ./btc \"input.file\"." << std::endl;
            return 1;
        }
        std::string filename = av[1];
        BitcoinExchange be;

        be.loadDatabase("data.csv");
        be.processInput(filename);
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}