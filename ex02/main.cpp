#include "PmergeMe.hpp"

int main(int ac, char **av) {
    if (ac < 2) {
        std::cerr << "Error: no arguments." << std::endl;
        return 1;
    }
    try {
        PmergeMe pm;
        pm.run(ac, av);
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
