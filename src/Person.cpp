#include "Person.hpp"



namespace lab_3
{
	Person::Person(const std::string& _name, const std::string& _surname) : name(_name), surname(_surname)
	{ }



	void Person::set_name(const std::string& _name) { name = _name; }



	void Person::set_surname(const std::string& _surname) { surname = _surname; }



	bool Person::is_valid() const
	{
		for (size_t i = 0; i < name.length(); ++i)
		{
			if (!isalpha(name[i]))		return false;
		}
		for (size_t i = 0; i < name.length(); ++i)
		{
			if (!isalpha(surname[i]))		return false;
		}
		return true;
	}



	std::istream& operator >> (std::istream& _in, Person& _right)
	{
		std::cout << "\tВВЕДИТЕ ИМЯ:\t\t";	_in >> _right.name;		std::cout << std::endl;
		rewind(stdin);
		std::cout << "\tВВЕДИТЕ ФАМИЛИЮ:\t\t";	_in >> _right.surname;		std::cout << std::endl;
		rewind(stdin);
		return _in;
	}



	std::ostream& operator << (std::ostream& _out, const Person& _right)
	{
		std::cout << std::setw(WIDTH_COLUMN) << _right.name << std::setw(WIDTH_COLUMN) << _right.surname;
		return _out;
	}



	std::ifstream& operator >> (std::ifstream& _fin, Person& _right)
	{
		_fin >> _right.name;
		_fin >> _right.surname;
		return _fin;
	}



	std::ofstream& operator << (std::ofstream& _fout, const Person& _right)
	{
		_fout << _right.name << ' ' << _right.surname;
		return _fout;
	}
}