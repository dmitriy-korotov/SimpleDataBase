#include "Date.hpp"

#include <cmath>



namespace my_date
{
	const std::unordered_set<std::string> Date::all_valid_month = { "January",		"ßíâàğü",
																	"February",		"Ôåâğàëü",
																	"March",		"Ìàğò",
																	"April",		"Àïğåëü",
																	"May",			"Ìàé",
																	"June",			"Èşíü",
																	"July",			"Èşëü",
																	"August",		"Àâãóñò",
																	"September",	"Ñåíòÿáğü",
																	"October",		"Îêòÿáğü",
																	"November",		"Íîÿáğü",
																	"December",		"Äåêàáğü"
																	"january",		"ÿíâàğü",
																	"february",		"ôåâğàëü",
																	"march",		"ìàğò",
																	"april",		"àïğåëü",
																	"may",			"ìàé",
																	"june",			"èşíü",
																	"july",			"èşëü",
																	"august",		"àâãóñò",
																	"september",	"ñåíòÿáğü",
																	"october",		"îêòÿáğü",
																	"november",		"íîÿáğü",
																	"december",		"äåêàáğü" };



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
		if (all_valid_month.find(_month) != all_valid_month.end())
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



	std::istream& operator>>(std::istream& _in, Date& _right)
	{
		std::string date_str;
		std::cout << "\tÂÂÅÄÈÒÅ ÄÀÒÓ Â ÔÎĞÌÀÒÅ ( ÄÅÍÜ-×ÈÑËÎ.ÌÅÑßÖ-ÑÒĞÎÊÀ.ÃÎÄ-×ÈÑËÎ ):\t\t";			_in >> date_str;

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
			std::cout << "\tÂÂÅÄÈÒÅ ÊÎĞĞÅÊÒÍÓŞ ÄÀÒÓ Â ÔÎĞÌÀÒÅ ( ÄÅÍÜ-×ÈÑËÎ.ÌÅÑßÖ-ÑÒĞÎÊÀ.ÃÎÄ-×ÈÑËÎ ):\t\t";
			_in >> date_str;

			fst_point = date_str.find_first_of('.');			scnd_point = date_str.find_last_of('.');
		}
		return _in;
	}



	std::ostream& operator<<(std::ostream& _out, const Date& _right)
	{
		_out << _right.day << '.' << _right.month << '.' << _right.year;
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