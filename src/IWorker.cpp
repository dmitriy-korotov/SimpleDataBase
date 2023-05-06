#include "IWorker.hpp"



namespace lab_4
{
	std::istream& operator >> (std::istream& _in, IWorker& _right)
	{
		_in >> _right.person;

		std::cout << "\tÂÂÅÄÈÒÅ ÏÐÎÔÅÑÑÈÞ ÐÀÁÎÒÍÈÊÀ:\t\t";	_in >> _right.profession;		std::cout << std::endl;
		rewind(stdin);
		return _in;
	}



	std::ostream& operator << (std::ostream& _out, const IWorker& _right)
	{
		std::cout << std::setw(WIDTH_COLUMN) << _right.person.get_name()
				  << std::setw(WIDTH_COLUMN) << _right.person.get_surname()
				  << std::setw(WIDTH_COLUMN) << _right.profession;
		return _out;
	}



	std::ifstream& operator >> (std::ifstream& _fin, IWorker& _right)
	{
		_fin >> _right.person;
		_fin >> _right.profession;
		return _fin;
	}



	std::ofstream& operator << (std::ofstream& _fout, const IWorker& _right)
	{
		_fout << _right.person << ' ' << _right.profession;
		return _fout;
	}
}