#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>

BitcoinExchange::BitcoinExchange()
{

}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &other)
{
	(void)other;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &other)
{
	if (this != &other)
	{

	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{

}

void    BitcoinExchange::loadDatabase(const std::string &filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file" << std::endl;
		return ;
	}

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line))
	{
		if (line.empty())
			continue;
		
		size_t sep = line.find(',');
		if (sep == std::string::npos)
			continue;
		
		std::string date = line.substr(0, sep);
		std::string ratestr = line.substr(sep + 1);

		double rate = ::atof(ratestr.c_str());

		_database[date] = rate;
	}
	file.close();
}

void    BitcoinExchange::processInput(const std::string &filename) const
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return ;
	}

	if (_database.empty())
	{
		std::cerr << "Error: database not loaded" << std::endl;
		return ;
	}

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line))
	{
		if (line.empty())
			continue;
	
		size_t sep = line.find(" | ");
		if (sep == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		
		std::string date = line.substr(0, sep);
		std::string valstr = line.substr(sep + 3);

		if (!isValidDate(date))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		if (!isValidNumber(valstr))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		double value = ::atof(valstr.c_str());

		if (value < 0)
		{
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		}

		if (value > 1000)
		{
			std::cerr << "Error: too large a number." << std::endl;
			continue;
		}

		double rate = getRateForDate(date);
		double result = value * rate;

		std::cout << date << " => " << value << " = " << result << std::endl;
	}

	file.close();
}

bool BitcoinExchange::isValidDate(const std::string &date) const
{
	if (date.size() != 10)
		return (false);

	if (date[4] != '-' || date[7] != '-')
		return (false);

	std::string yearStr = date.substr(0, 4);
	std::string monthStr = date.substr(5, 2);
	std::string dayStr = date.substr(8, 2);

	for (int i = 0; i < 4; i++)
		if (!isdigit(yearStr[i]))
			return (false);

	for (int i = 0; i < 2; i++)
		if (!isdigit(monthStr[i]) || !isdigit(dayStr[i]))
			return (false);

	int year = std::atoi(yearStr.c_str());    
	int month = std::atoi(monthStr.c_str());
	int day = std::atoi(dayStr.c_str());

	if (month < 1 || month > 12)
		return (false);

	int maxDay;
	switch (month)
	{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			maxDay = 31; break;
		case 4: case 6: case 9: case 11:
			maxDay = 30; break;
		case 2:
			maxDay = 29; break;
		default:
			return (false);
	}

	if (day < 1 || day > maxDay)
		return (false);

	if (year < 1970 || year > 2038)
		return (false);

	return (true);
}

bool BitcoinExchange::isValidNumber(const std::string &valStr) const
{
	bool frac = false;

	for (size_t i = 0; i < valStr.size(); i++)
	{
		if (valStr[i] == '.')
		{
			if (frac)
				return false;
			frac = true;
		}
		else if (!isdigit(valStr[i]))
			return false;
	}

	return true;
}

double BitcoinExchange::getRateForDate(const std::string &date) const
{
    std::map<std::string, double>::const_iterator it = _database.lower_bound(date);

    if (it == _database.end())
    {
        --it;
        return it->second;
    }

    if (it->first == date)
        return it->second;

    if (it == _database.begin())
        return it->second;

    --it;
    return it->second;
}

const std::map<std::string, double>& BitcoinExchange::getDatabase() const
{
	return _database;
}
