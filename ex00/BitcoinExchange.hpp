#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <string>
# include <map>

class BitcoinExchange
{
    public:
        BitcoinExchange();
        BitcoinExchange(BitcoinExchange const &other);
        BitcoinExchange &operator=(BitcoinExchange const &other);
        ~BitcoinExchange();

        void    loadDatabase(const std::string &filename);
        const   std::map<std::string, double>& getDatabase() const;
        void    processInput(const std::string &filename) const;
        bool    isValidNumber(const std::string &valStr) const;
        bool    isValidDate(const std::string &date) const;
        double  getRateForDate(const std::string &date) const;

    private:
        std::map<std::string, double> _database;
};

#endif