#include "PmergeMe.hpp"
#include <iostream>
#include <cstdlib>  // std::strtol
#include <climits>  // INT_MAX
#include <cctype>   // isdigit
#include <algorithm>
#include <ctime>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other)
{
    (void)other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    (void)other;
    return *this;
}

PmergeMe::~PmergeMe() {}

std::deque<int> PmergeMe::mergeInsertSortDeque(const std::deque<int> &input)
{
    std::deque<int> big;
    std::deque<int> small;

    // make pairs
    for (size_t i = 0; i < input.size(); i += 2)
    {
        if (i + 1 < input.size())
        {
            int a = input[i];
            int b = input[i + 1];

            if (a > b)
            {
                big.push_back(a);
                small.push_back(b);
            }
            else
            {
                big.push_back(b);
                small.push_back(a);
            }
        }
        else
        {
            big.push_back(input[i]);
        }
    }

    // sort big
    std::sort(big.begin(), big.end());

    // insert small
    for (size_t i = 0; i < small.size(); ++i)
    {
        int value = small[i];
        std::deque<int>::iterator pos =
            std::lower_bound(big.begin(), big.end(), value);
        big.insert(pos, value);
    }

    return big;
}

std::vector<int> PmergeMe::mergeInsertSortVector(const std::vector<int> &input)
{
    std::vector<int> big;
    std::vector<int> small;

    // Make pairs
    for (size_t i = 0; i < input.size(); i += 2)
    {
        if (i + 1 < input.size())
        {
            int a = input[i];
            int b = input[i + 1];

            if (a > b)
            {
                big.push_back(a);
                small.push_back(b);
            }
            else
            {
                big.push_back(b);
                small.push_back(a);
            }
        }
        else
            big.push_back(input[i]);
    }

    std::sort(big.begin(), big.end());
    
    // Merge debug
    std::cout << "[DEBUG] big: ";
    for (size_t i = 0; i < big.size(); ++i) std::cout << big[i] << " ";
    std::cout << "\n[DEBUG] small: ";
    for (size_t i = 0; i < small.size(); ++i) std::cout << small[i] << " ";
    std::cout << std::endl;
    

    // binary search + insert
    for (size_t i = 0; i < small.size(); ++i)
    {
        int value = small[i];

        // find insert pos
        std::vector<int>::iterator pos =
            std::lower_bound(big.begin(), big.end(), value);

        big.insert(pos, value);
    }

    return big;
}

int PmergeMe::parseNumber(const std::string &s) const
{
    if (s.empty())
        throw std::runtime_error("Error");

    // only digits check
    for (size_t i = 0; i < s.size(); ++i)
    {
        if (!std::isdigit(s[i]))
            throw std::runtime_error("Error");
    }

    // avoid int max
    long num = std::strtol(s.c_str(), NULL, 10);

    if (num <= 0 || num > INT_MAX)
        throw std::runtime_error("Error");

    return static_cast<int>(num);
}


void PmergeMe::process(int argc, char **argv)
{
    // Parse & store in vectors
    for (int i = 1; i < argc; ++i)
    {
        int value = parseNumber(argv[i]);

        _vector.push_back(value);
        _deque.push_back(value);
    }

    // Before
    std::cout << "Before: ";
    for (size_t i = 0; i < _vector.size(); ++i)
        std::cout << _vector[i] << " ";
    std::cout << std::endl;
    // vector sort
    clock_t startVec = clock();
    std::vector<int> sortedVec = mergeInsertSortVector(_vector);
    clock_t endVec = clock();
    double vectorTime = static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1e6;
    _vector = sortedVec;
    // After
    std::cout << "After: ";
    for (size_t i = 0; i < _vector.size(); ++i)
        std::cout << _vector[i] << " ";
    std::cout << std::endl;



    // DEQUE version
    clock_t startDeq = clock();
    std::deque<int> sortedDeq = mergeInsertSortDeque(_deque);
    clock_t endDeq = clock();
    double dequeTime = static_cast<double>(endDeq - startDeq) / CLOCKS_PER_SEC * 1e6;

    // Times
    std::cout << "Time to process a range of "
              << sortedVec.size()
              << " elements with std::vector : "
              << vectorTime
              << " us"
              << std::endl;

    std::cout << "Time to process a range of "
              << sortedDeq.size()
              << " elements with std::deque : "
              << dequeTime
              << " us"
              << std::endl;
}

