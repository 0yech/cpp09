#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>
# include <string>

class PmergeMe
{
    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        ~PmergeMe();

        void process(int argc, char **argv);

    private:
        std::vector<int> _vector;
        std::deque<int>  _deque;

        int parseNumber(const std::string &s) const;
        std::vector<int> mergeInsertSortVector(const std::vector<int> &input);
        std::deque<int> mergeInsertSortDeque(const std::deque<int> &input);
};

#endif
