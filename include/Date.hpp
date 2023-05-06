#pragma once
#ifndef DATE_HPP
#define DATE_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>



namespace my_date
{
	class Date
	{
	public:

		friend std::istream& operator>>(std::istream& _in, Date& _right);
		friend std::ostream& operator<<(std::ostream& _out, const Date& _right);
		friend std::ifstream& operator>>(std::ifstream& _fin, Date& _right);
		friend std::ofstream& operator<<(std::ofstream& _fout, const Date& _right);

		Date() = default;
		Date(const Date&) = default;
		Date& operator=(const Date&) = default;

		Date(unsigned int _day, const std::string& _month, unsigned int _year);

		bool setDay(unsigned int _day);
		bool setMonth(const std::string& _month);
		bool setYear(unsigned int _year);
		bool setDate(unsigned int _day, const std::string& _month, unsigned int _year);

		unsigned int getDay() const { return day; }
		std::string getMonth() const { return month; }
		unsigned int getYear() const { return year; }

	private:

		static bool is_valid_date(const std::string& date_str);
		static unsigned int from_str_to_uint(const std::string& str);

	private:

		const static std::unordered_set<std::string> all_valid_month;

	private:

		unsigned int day = 0;
		unsigned int year = 1978;
		std::string month;

	};	
}
#endif // !DATE_HPP