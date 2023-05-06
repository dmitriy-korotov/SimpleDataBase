#pragma once
#ifndef MAN_HPP
#define MAN_HPP

#include "Settings.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>



namespace lab_3
{
	class Man
	{
	public:

		friend std::istream& operator >> (std::istream& _in, Man& _right);
		friend std::ostream& operator << (std::ostream& _out, const Man& _right);
		friend std::ifstream& operator >> (std::ifstream& _fin, Man& _right);
		friend std::ofstream& operator << (std::ofstream& _fout, const Man& _right);



		Man() = default;
		Man(const Man&) = default;
		Man& operator=(const Man&) = default;
		~Man() = default;

		Man(const std::string& _name, const std::string& _surname);

		bool operator==(const Man& _right) { return name == _right.name && surname == _right.surname; }

		void set_name(const std::string& _name);
		void set_surname(const std::string& _surname);

		bool is_valid() const;

		const std::string& get_name() const { return name; }
		const std::string& get_surname() const { return surname; }

	private:

		std::string name;
		std::string surname;

	};
}

#endif // !MAN_HPP