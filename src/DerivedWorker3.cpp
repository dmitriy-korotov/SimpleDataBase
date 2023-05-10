#include "DerivedWorker3.hpp"

#include "Settings.hpp"



namespace lab_6
{
	void DerivedWorker3::set_job_title(const std::string _job_title) noexcept
	{
		job_title = _job_title;
	}



	const std::string& DerivedWorker3::get_job_title() const noexcept
	{
		return job_title;
	}



	bool DerivedWorker3::is_valid() const
	{
		for (char symbol : job_title)
		{
			if (!std::isalpha(symbol))
			{
				return false;
			}
		}
		return true;
	}



	std::istream& operator >> (std::istream& _in, DerivedWorker3& _right)
	{
		_in >> static_cast<lab_4::DerivedWorker2&>(_right);
		std::cout << "\tÂÂÅÄÈÒÅ ÄÎËÆÍÎÑÒÜ:\t\t";		_in >> _right.job_title;		std::cout << std::endl;
		return _in;
	}



	std::ostream& operator << (std::ostream& _out, const DerivedWorker3& _right)
	{
		_out << static_cast<const lab_4::DerivedWorker2&>(_right);
		_out << std::setw(WIDTH_COLUMN) << _right.job_title;
		return _out;
	}



	std::ifstream& operator >> (std::ifstream& _fin, DerivedWorker3& _right)
	{
		_fin >> static_cast<lab_4::DerivedWorker2&>(_right);
		_fin >> _right.job_title;
		return _fin;
	}



	std::ofstream& operator << (std::ofstream& _fout, const DerivedWorker3& _right)
	{
		_fout << static_cast<const lab_4::DerivedWorker2&>(_right) << ' ';
		_fout << _right.job_title;
		return _fout;
	}



	void DerivedWorker3::show_titles() noexcept
	{
		lab_4::DerivedWorker2::show_titles();
		std::cout << std::setw(WIDTH_COLUMN) << std::left << "ÄÎËÆÍÎÑÒÜ";
	}
}