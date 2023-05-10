#pragma once
#ifndef PERSON_HPP
#define PERSON_HPP

#include "Settings.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>



namespace lab_3
{
	class Person
	{
	public:

		friend std::istream& operator >> (std::istream& _in, Person& _right);
		friend std::ostream& operator << (std::ostream& _out, const Person& _right);
		friend std::ifstream& operator >> (std::ifstream& _fin, Person& _right);
		friend std::ofstream& operator << (std::ofstream& _fout, const Person& _right);



		Person() = default;
		Person(const Person&) = default;
		Person& operator=(const Person&) = default;
		~Person() = default;

		Person(const std::string& _name, const std::string& _surname);

		bool operator==(const Person& _right) { return name == _right.name && surname == _right.surname; }

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

#endif // !PERSON_HPP