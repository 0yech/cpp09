#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}

void PmergeMe::fordJohnson(vec &c)
{
    fordJohnsonImpl(c);
}

void PmergeMe::fordJohnson(deq &c)
{
    fordJohnsonImpl(c);
}

std::vector<size_t> PmergeMe::jacobSequence(size_t n)
{
    std::vector<size_t> jac;
    if (n <= 1)
        return jac;

    // init jacob sequence
    jac.push_back(1);
    size_t j1 = 1, j2 = 1;

    // stops when j2 >= n
    while (j2 < n)
    {
        size_t j = j2 + 2 * j1;
        jac.push_back(j);
        j1 = j2;
        j2 = j;
    }

    // order stores the min insert order
    std::vector<size_t> order;
    size_t prev = 1;

    for (size_t i = 0; i < jac.size(); i++)
    {
        // set limit at n when highest jac value reached.
        size_t limit = (jac[i] < n ? jac[i] : n);
        for (size_t k = limit; k > prev; k--)
            order.push_back(k - 1);
        prev = limit;
        if (limit == n)
            break;
    }
    return order;
}

void PmergeMe::printTime(double tVec, double tDeq, size_t size)
{
    std::cout << "Time to process " << size
              << " elements with std::vector : " << tVec << " us\n";

    std::cout << "Time to process " << size
              << " elements with std::deque  : " << tDeq << " us\n";
}

void PmergeMe::sort(const std::vector<int> &input)
{
    vec v(input.begin(), input.end());
    deq d(input.begin(), input.end());

    std::cout << "Before: ";
    for (size_t i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";
    std::cout << "\n";

    clock_t sv = clock();
    fordJohnson(v);
    clock_t ev = clock();

    clock_t sd = clock();
    fordJohnson(d);
    clock_t ed = clock();

    std::cout << "After: ";
    for (size_t i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";
    std::cout << "\n";

    printTime(
        (double)(ev - sv) / CLOCKS_PER_SEC * 1e6,
        (double)(ed - sd) / CLOCKS_PER_SEC * 1e6,
        v.size()
    );
}
