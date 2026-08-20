#pragma once
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <stdexcept>
#include <ctime>

class PmergeMe {

    private:
        std::vector<int> _vec;
        std::deque<int>  _deq;

    void parseArgs(int ac, char **av);

    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        ~PmergeMe();

        void run(int ac, char **av);
};
