#include "DerivedWorker2.hpp"



namespace lab_4
{
	std::istream& operator >> (std::istream& _in, DerivedWorker2& _right)
	{
		_in >> static_cast<IWorker&>(_right);
		std::cout << "\tÂÂÅÄÈÒÅ ÄÀÒÓ ÏÐÈÍßÒÈß ÍÀ ÐÀÁÎÒÓ Â ÔÎÐÌÀÒÅ ( ÄÅÍÜ-×ÈÑËÎ.ÌÅÑßÖ-ÑÒÐÎÊÀ.ÃÎÄ-×ÈÑËÎ ):\t\t";
		_in >> _right.date;			std::cout << std::endl;
		return _in;
	}



	std::ostream& operator << (std::ostream& _out, const DerivedWorker2& _right)
	{
		_out << static_cast<const IWorker&>(_right);
		_out << std::setw(WIDTH_COLUMN) << _right.date;
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



	my_date::Date DerivedWorker2::getDate() const noexcept
	{
		return date;
	}



	void DerivedWorker2::show_titles() noexcept
	{
		std::cout << '\t'
			<< std::setw(WIDTH_COLUMN) << std::left << "ÍÎÌÅÐ ÇÀÏÈÑÈ"
			<< std::setw(WIDTH_COLUMN) << std::left << "ÈÌß"
			<< std::setw(WIDTH_COLUMN) << std::left << "ÔÀÌÈËÈß"
			<< std::setw(WIDTH_COLUMN) << std::left << "ÏÐÎÔÅÑÑÈß"
			<< std::setw(WIDTH_COLUMN) << std::left << "ÄÀÒÀ ÏÎÑÒÓÏËÅÍÈß";
	}
}