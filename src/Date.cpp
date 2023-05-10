#include "Date.hpp"

#include <cmath>



namespace my_date
{
	const std::unordered_map<std::string, uint8_t> Date::monthes = { std::pair{"January" ,	1},		std::pair{"ßíâàðü",		1},
																	 std::pair{"February",	2},		std::pair{"Ôåâðàëü",	2},
																	 std::pair{"March",		3},		std::pair{"Ìàðò",		3},
																	 std::pair{"April",		4},		std::pair{"Àïðåëü",		4},
																	 std::pair{"May",		5},		std::pair{"Ìàé",		5},
																	 std::pair{"June",		6},		std::pair{"Èþíü",		6},
																	 std::pair{"July",		7},		std::pair{"Èþëü",		7},
																	 std::pair{"August",	8},		std::pair{"Àâãóñò",		8},
																	 std::pair{"September", 9},		std::pair{"Ñåíòÿáðü",	9},
																	 std::pair{"October",	10},	std::pair{"Îêòÿáðü",	10},
																	 std::pair{"November",	11},	std::pair{"Íîÿáðü",		11},
																	 std::pair{"December",	12},	std::pair{"Äåêàáðü",	12},
																	 std::pair{"january",	1},		std::pair{"ÿíâàðü",		1},
																	 std::pair{"february",	2},		std::pair{"ôåâðàëü",	2},
																	 std::pair{"march",		3},		std::pair{"ìàðò",		3},
																	 std::pair{"april",		4},		std::pair{"àïðåëü",		4},
																	 std::pair{"may",		5},		std::pair{"ìàé",		5},
																	 std::pair{"june",		6},		std::pair{"èþíü",		6},
																	 std::pair{"july",		7},		std::pair{"èþëü",		7},
																	 std::pair{"august",	8},		std::pair{"àâãóñò",		8},
																	 std::pair{"september",	9},		std::pair{"ñåíòÿáðü",	9},
																	 std::pair{"october",	10},	std::pair{"îêòÿáðü",	10},
																	 std::pair{"november",	11},	std::pair{"íîÿáðü",		11},
																	 std::pair{"december",	12},	std::pair{"äåêàáðü",	12} };



	Date::Date(unsigned int _day, const std::string& _month, unsigned int _year)
			: day(_day)
			, month(_month)
			, year(_year)
	{ }



	bool Date::setDay(unsigned int _day)
	{
		if (_day > 0 && _day < 32)
		{
			day = _day;
			return true;
		}
		return false;
	}



	bool Date::setMonth(const std::string& _month)
	{
		if (monthes.find(_month) != monthes.end())
		{
			month = _month;
			return true;
		}
		return false;
	}



	bool Date::setYear(unsigned int _year)
	{
		if (_year < 2024)
		{
			year = _year;
			return true;
		}
		return false;
	}



	bool Date::setDate(unsigned int _day, const std::string& _month, unsigned int _year)
	{
		if (!setDay(_day))			return false;
		if (!setMonth(_month))		return false;
		if (!setYear(_year))		return false;
		return true;
	}



	bool Date::is_valid_date(const std::string& date_str)
	{
		size_t fst_point_index = date_str.find('.', 0);
		if (fst_point_index > date_str.length())		return false;

		size_t last_point_index = date_str.rfind('.', date_str.length());
		if (last_point_index > date_str.length())		return false;

		for (size_t i = 0; i < date_str.length(); ++i)
		{
			if (i < fst_point_index && !isdigit(date_str[i]))								return false;
			if (fst_point_index < i && i < last_point_index && !isalpha(date_str[i]))		return false;
			if (i > last_point_index && !isdigit(date_str[i]))								return false;
		}
		return true;
	}



	unsigned int Date::from_str_to_uint(const std::string& str)
	{
		unsigned int result = 0;
		for (unsigned int i = 0, index_digit = static_cast<unsigned int>(str.length() - 1); i < str.length(); --index_digit, ++i)
		{
			result += static_cast<unsigned int>(std::pow(10, i)) * (str[index_digit] - 48);
		}

		return result;
	}



	uint64_t Date::difference(const Date& _other) const noexcept
	{
		return std::abs(static_cast<int8_t>(day - _other.day))
			   + 
			   std::abs(static_cast<int8_t>(monthes.at(month) - monthes.at(month))) * 31
			   +
			   std::abs(static_cast<int16_t>(year - _other.year)) * 31 * 12;
	}



	Date::Month Date::castToMonthes(Day _days) noexcept
	{
		return _days / 31;
	}



	Date::Year Date::castToYears(Day _days) noexcept
	{
		return _days / (31 * 12);
	}



	std::istream& operator>>(std::istream& _in, Date& _right)
	{
		std::string date_str;
		_in >> date_str;

		size_t fst_point = date_str.find_first_of('.');
		size_t scnd_point = date_str.find_last_of('.');

		while (
			!Date::is_valid_date(date_str)
			||
			!_right.setDate(Date::from_str_to_uint(date_str.substr(0, fst_point)),
				date_str.substr(fst_point + 1, scnd_point - fst_point - 1),
				Date::from_str_to_uint(date_str.substr(scnd_point + 1, date_str.length())))
			)
		{
			rewind(stdin);
			std::cout << std::endl;
			std::cout << "\tÂÂÅÄÈÒÅ ÊÎÐÐÅÊÒÍÓÞ ÄÀÒÓ Â ÔÎÐÌÀÒÅ ( ÄÅÍÜ-×ÈÑËÎ.ÌÅÑßÖ-ÑÒÐÎÊÀ.ÃÎÄ-×ÈÑËÎ ):\t\t";
			_in >> date_str;

			fst_point = date_str.find_first_of('.');			scnd_point = date_str.find_last_of('.');
		}
		return _in;
	}



	std::ostream& operator<<(std::ostream& _out, const Date& _right)
	{
		_out << (std::to_string(_right.day) + '.' + _right.month + '.' + std::to_string(_right.year));
		return _out;
	}



	std::ifstream& operator>>(std::ifstream& _fin, Date& _right)
	{
		std::string temp;
		_fin >> temp;

		size_t fst_point = temp.find_first_of('.');
		size_t scnd_point = temp.find_last_of('.');

		_right.setDate(Date::from_str_to_uint(temp.substr(0, fst_point)),
					   temp.substr(fst_point + 1, scnd_point - fst_point - 1),
					   Date::from_str_to_uint(temp.substr(scnd_point + 1, temp.length())));

		return _fin;
	}



	std::ofstream& operator<<(std::ofstream& _fout, const Date& _right)
	{
		_fout << _right.day << '.' << _right.month << '.' << _right.year;
		return _fout;
	}
}