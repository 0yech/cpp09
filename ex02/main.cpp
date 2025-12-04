#include "PmergeMe.hpp"
#include <cstdlib>

int main(int ac, char **av)
{
    if (ac < 2) {
        std::cout << "Error: not enough arguments\n";
        return 1;
    }

    std::vector<int> numbers;

    for (int i = 1; i < ac; i++)
    {
        std::string s(av[i]);
        for (size_t j = 0; j < s.size(); j++)
        {
            if (!isdigit(s[j]))
            {
                std::cout << "Error\n";
                return (1);
            }
        }

        long n = std::atol(av[i]);
        if (n < 0 || n > 2147483647)
        {
            std::cout << "Error\n";
            return (1);
        }
        numbers.push_back(n);
    }
    PmergeMe sorter;
    sorter.sort(numbers);
}
