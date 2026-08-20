#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other) : _vec(other._vec), _deq(other._deq) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
    if (this != &other) {
        _vec = other._vec;
        _deq = other._deq;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

void PmergeMe::parseArgs(int ac, char **av) {
    for (int i = 1; i < ac; i++) {
        std::string s(av[i]);

        if (s.empty())
            throw std::runtime_error("Error");
        for (size_t j = 0; j < s.size(); j++) {
            if (!std::isdigit(s[j]))
                throw std::runtime_error("Error");
        }

        long val = std::strtol(s.c_str(), NULL, 10);
        if (val <= 0 || val > 2147483647L)
            throw std::runtime_error("Error");

        _vec.push_back((int)val);
        _deq.push_back((int)val);
    }
}

static std::vector<int> getJacobsthalOrder(int n) {
    if (n <= 0)
        return std::vector<int>();

    std::vector<int> jac;
    jac.push_back(1);
    jac.push_back(3);
    while (jac.back() < n)
        jac.push_back(jac[jac.size()-1] + 2 * jac[jac.size()-2]);

    std::vector<int> order;
    std::vector<bool> done(n + 1, false);

    for (size_t k = 0; k < jac.size(); k++) {
        int end   = jac[k];
        int start = (k == 0) ? 1 : jac[k-1] + 1;

        for (int idx = end; idx >= start; idx--) {
            if (idx <= n && !done[idx]) {
                order.push_back(idx);
                done[idx] = true;
            }
        }
    }
    return order;
}

template <typename T>
static void fordJohnson(T &arr) {
    
    // --recursive condition
    int n = (int)arr.size();
    if (n <= 1)
        return ;

    bool hasStraggler = (n % 2 == 1);
    int straggler = hasStraggler ? arr[n - 1] : 0;
    int pairsEnd  = hasStraggler ? n - 1 : n;


    // --putting highers in left position
    for (int i = 0; i + 1 < pairsEnd; i += 2) {
        if (arr[i] < arr[i + 1])
            std::swap(arr[i], arr[i + 1]);
    }

    T highers;
    T lowers;

    for (int i = 0; i + 1 < pairsEnd; i += 2) {
        highers.push_back(arr[i]);
        lowers.push_back(arr[i + 1]);
    }

    // --building pairs
    std::vector<std::pair<int,int> > pairs;
    for (size_t i = 0; i < highers.size(); i++)
        pairs.push_back(std::make_pair(highers[i], lowers[i]));

    // --sorting highers group only
    fordJohnson(highers);

    // --searching lowers and connect it to the highers
    T pend;
    for (size_t i = 0; i < highers.size(); i++) {
        for (size_t j = 0; j < pairs.size(); j++) {
            if (pairs[j].first == highers[i]) {
                pend.push_back(pairs[j].second);
                pairs.erase(pairs.begin() + j);
                break;
            }
        }
    }

    T main_chain;
    main_chain.push_back(pend[0]);
    for (size_t i = 0; i < highers.size(); i++)
        main_chain.push_back(highers[i]);

    T pendToInsert;
    for (size_t i = 1; i < pend.size(); i++)
        pendToInsert.push_back(pend[i]);
    if (hasStraggler)
        pendToInsert.push_back(straggler);

    std::vector<int> order = getJacobsthalOrder((int)pendToInsert.size());

    for (size_t oi = 0; oi < order.size(); oi++) {
        int idx = order[oi] - 1;

        if (idx >= (int)pendToInsert.size())
            continue;

        int val = pendToInsert[idx];

        typename T::iterator pos = std::lower_bound(main_chain.begin(), main_chain.end(), val);
        main_chain.insert(pos, val);
    }
    arr = main_chain;
}

void PmergeMe::run(int ac, char **av) {
    parseArgs(ac, av);

    std::cout << "Before:";
    for (size_t i = 0; i < _vec.size(); i++)
        std::cout << " " << _vec[i];
    std::cout << std::endl;

    clock_t t1 = clock();
    fordJohnson(_vec);
    clock_t t2 = clock();

    clock_t t3 = clock();
    fordJohnson(_deq);
    clock_t t4 = clock();

    std::cout << "After: ";
    for (size_t i = 0; i < _vec.size(); i++)
        std::cout << " " << _vec[i];
    std::cout << std::endl;

    double timeVec = (double)(t2 - t1) / CLOCKS_PER_SEC * 1000000.0;
    double timeDeq = (double)(t4 - t3) / CLOCKS_PER_SEC * 1000000.0;

    std::cout << "Time to process a range of " << _vec.size()
              << " elements with std::vector : " << timeVec << " us" << std::endl;
    std::cout << "Time to process a range of " << _deq.size()
              << " elements with std::deque  : " << timeDeq << " us" << std::endl;
}
