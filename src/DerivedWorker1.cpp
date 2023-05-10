#include "DerivedWorker1.hpp"



namespace lab_3
{
	DerivedWorker1::DerivedWorker1(const Person& person)
		: IWorker(person)
	{ }



	DerivedWorker1::DerivedWorker1(const std::string& _name, const std::string& _surname, const std::string& _profession,
				   unsigned int _department_number, float _salary)
			: IWorker(_name, _surname, _profession)
			, department_number(_department_number)
			, salary(_salary)
	{ }



	void DerivedWorker1::set_department_number(const unsigned int _department_number) { department_number = _department_number; }



	void DerivedWorker1::set_salary(const float _salary) { salary = _salary; }



	bool DerivedWorker1::is_valid() const
	{
		if (!person.is_valid())		return false;
		return department_number > 0 && salary > 0;
	}



	bool DerivedWorker1::operator==(const Person& _right)
	{
		return this->person == _right;
	}



	std::istream& operator >> (std::istream& _in, DerivedWorker1& _right)
	{
		_in >> static_cast<lab_4::IWorker&>(_right);

		std::cout << "\tÂÂÅÄÈÒÅ ÍÎÌÅÐ ÎÒÄÅËÀ ÐÀÁÎÒÍÈÊÀ:\t\t";		_in >> _right.department_number;	std::cout << std::endl;
		rewind(stdin);
		while (_in.fail())
		{
			_in.clear();
			rewind(stdin);
			std::cout << "\tÂÂÅÄÈÒÅ ÊÎÐÐÅÊÒÍÛÉ ÍÎÌÅÐ ÎÒÄÅËÀ ÐÀÁÎÒÍÈÊÀ:\t\t";	_in >> _right.department_number;	std::cout << std::endl;
		}

		std::cout << "\tÂÂÅÄÈÒÅ ÎÊËÀÄ ÐÀÁÎÒÍÈÊÀ:\t\t";				_in >> _right.salary;				std::cout << std::endl;
		rewind(stdin);
		while (_in.fail())
		{
			_in.clear();
			rewind(stdin);
			std::cout << "\tÂÂÅÄÈÒÅ ÊÎÐÐÅÊÒÍÛÉ ÎÊËÀÄ ÐÀÁÎÒÍÈÊÀ:\t\t";	_in >> _right.salary;	std::cout << std::endl;
		}
		return _in;
	}



	std::ofstream& operator << (std::ofstream& _fout, const DerivedWorker1& _right)
	{	
		_fout << static_cast<const lab_4::IWorker&>(_right);
		_fout << ' ' << _right.department_number << ' ';
		_fout << _right.salary;
		return _fout;
	}



	std::ifstream& operator >> (std::ifstream& _fin, DerivedWorker1& _right)
	{
		_fin >> static_cast<lab_4::IWorker&>(_right);
		_fin >> _right.department_number;
		_fin >> _right.salary;
		return _fin;
	}



	std::ostream& operator << (std::ostream& _out, const DerivedWorker1& _right)
	{
		
		_out << std::setw(WIDTH_COLUMN) << static_cast<const lab_4::IWorker&>(_right)
			 << std::setw(WIDTH_COLUMN) << std::left << _right.department_number
			 << std::setw(WIDTH_COLUMN) << std::left << _right.salary;
		return _out;
	}



	void DerivedWorker1::show_titles() noexcept
	{
		std::cout << '\t'
			<< std::setw(WIDTH_COLUMN) << std::left << "ÍÎÌÅÐ ÇÀÏÈÑÈ"
			<< std::setw(WIDTH_COLUMN) << std::left << "ÈÌß"
			<< std::setw(WIDTH_COLUMN) << std::left << "ÔÀÌÈËÈß"
			<< std::setw(WIDTH_COLUMN) << std::left << "ÏÐÎÔÅÑÑÈß"
			<< std::setw(WIDTH_COLUMN) << std::left << "ÍÎÌÅÐ ÎÒÄÅËÀ"
			<< std::setw(WIDTH_COLUMN) << std::left << "ÎÊËÀÄ";
	}
}