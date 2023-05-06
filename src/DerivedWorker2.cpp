#include "DerivedWorker2.hpp"



namespace lab_4
{
	std::istream& operator >> (std::istream& _in, DerivedWorker2& _right)
	{
		_in >> static_cast<IWorker&>(_right);
		_in >> _right.date;
		return _in;
	}



	std::ostream& operator << (std::ostream& _out, DerivedWorker2& _right)
	{
		_out << static_cast<IWorker&>(_right) << _right.date << '\n';
		return _out;
	}



	std::ofstream& operator << (std::ofstream& _fout, const DerivedWorker2& _right)
	{
		_fout << static_cast<const lab_4::IWorker&>(_right);
		_fout << ' ';
		_fout << _right.date;
		return _fout;
	}



	std::ifstream& operator >> (std::ifstream& _fin, DerivedWorker2& _right)
	{
		_fin >> static_cast<lab_4::IWorker&>(_right);
		_fin >> _right.date;
		return _fin;
	}



	bool DerivedWorker2::is_valid() const
	{
		return true;
	}



	void DerivedWorker2::show_titles()
	{
		std::cout << '\t'
				  << std::setw(WIDTH_COLUMN) << std::left << "ÍÎÌÅÐ ÇÀÏÈÑÈ"
				  << std::setw(WIDTH_COLUMN) << std::left << "ÈÌß"
				  << std::setw(WIDTH_COLUMN) << std::left << "ÔÀÌÈËÈß"
				  << std::setw(WIDTH_COLUMN) << std::left << "ÏÐÎÔÅÑÑÈß"
				  << std::setw(WIDTH_COLUMN) << std::left << "ÄÀÒÀ ÏÎÑÒÓÏËÅÍÈß" << std::endl;
	}
}