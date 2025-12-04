#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <stdexcept>
#include <ctime>

class PmergeMe {

public:
    typedef std::vector<int> vec;
    typedef std::deque<int>  deq;

    PmergeMe();
    ~PmergeMe();

    void sort(const std::vector<int> &input);

private:

    struct Pair
    {
        int max;
        int min;
        Pair(int a, int b) : max(a), min(b) {}
    };

    void fordJohnson(vec &c);
    void fordJohnson(deq &c);

    std::vector<size_t> jacobSequence(size_t n);
    void printTime(double tVec, double tDeq, size_t size);

    // Making pairs and Sorting maxes recursively until one last max remains.
    // Align max/small pairs based on sorted maxes.
    // Insert the nodes' maxes into main container.
    // Insert min0 immediately as the weakest max's min pair will be placed correctly.
    // Build a vector filled with the algo's sorting order based on Jacobsthal's sequence.
    // Insert optimal mins into main by following Jacobsthal's sequence.
    // Insert straggler as min if needed.

    template<typename C>
    void fordJohnsonImpl(C &c)
    {
        // end recursion when maxes are sorted
        if (c.size() <= 1)
            return;

        // 1. Make pairs
        std::vector<Pair> pairs;
        int straggler;
        makePairs(c, pairs, straggler);

        // 2. Sort max values recursively
        C maxes;
        for (size_t i = 0; i < pairs.size(); i++)
            maxes.push_back(pairs[i].max);

        fordJohnsonImpl(maxes);

        // 3. Rebuild pairs sorted by max
        std::vector<Pair> sortedPairs;
        for (size_t i = 0; i < maxes.size(); i++)
        {
            for (size_t j = 0; j < pairs.size(); j++)
            {
                if (pairs[j].max == maxes[i])
                {
                    sortedPairs.push_back(pairs[j]);
                    break;
                }
            }
        }
        pairs = sortedPairs;

        C main;
        for (size_t i = 0; i < pairs.size(); i++)
            main.push_back(pairs[i].max);

        // min0 insert
        main.insert(main.begin(), pairs[0].min);


        std::vector<size_t> order = jacobSequence(pairs.size());
        for (size_t k = 0; k < order.size(); k++)
        {
            size_t idx = order[k];
            int small = pairs[idx].min;

            // Insert using binary search
            size_t pos = binarySearchPos(main, small, main.size());
            main.insert(main.begin() + pos, small);
        }

        if (straggler != -1)
        {
            size_t pos = binarySearchPos(main, straggler, main.size());
            main.insert(main.begin() + pos, straggler);
        }

        c = main;
    }

    // ---------------------- Helpers -----------------------

    template<typename C>
    void makePairs(const C &src, std::vector<Pair> &pairs, int &straggler)
    {
        size_t i = 0;
        size_t n = src.size();

        while (i + 1 < n)
        {
            int a = src[i];
            int b = src[i + 1];

            if (a > b)
                pairs.push_back(Pair(a, b));
            else
                pairs.push_back(Pair(b, a));
            i += 2;
        }

        // odd amount of nums
        if (n % 2 == 1)
            straggler = src[n - 1];
        else
            straggler = -1;
    }

    template<typename C>
    size_t binarySearchPos(const C &c, int value, size_t end)
    {
        size_t left = 0;
        size_t right = end;
        while (left < r)
        {
            size_t mid = (left + right) / 2;
            if (c[mid] < value)
                left = mid + 1;
            else
                right = mid;
        }
        return left;
    }
};

#endif
