#pragma once
#ifndef DERIVED_WORKER_2_HPP
#define DERIVED_WORKER_2_HPP

#include "Settings.hpp"
#include "IWorker.hpp"
#include "Date.hpp"

#include <iomanip>



namespace lab_4
{ 
	class DerivedWorker2 : public IWorker
	{
	public:

		friend std::istream& operator >> (std::istream& _in, DerivedWorker2& _right);
		friend std::ostream& operator << (std::ostream& _out, DerivedWorker2& _right);
		friend std::ifstream& operator >> (std::ifstream& _in, DerivedWorker2& _right);
		friend std::ofstream& operator << (std::ofstream& _out, const DerivedWorker2& _right);



		DerivedWorker2() = default;
		DerivedWorker2(const std::string& _name, const std::string& _surname, const std::string& _profession, const my_date::Date& _date)
			: IWorker(_name, _surname, _profession)
			, date(_date)
		{ }

		bool operator == (const lab_3::Man& _right) { return person == _right; }
		bool operator < (const DerivedWorker2& _right) { return date.getYear() < _right.date.getYear(); }
		bool operator > (const DerivedWorker2& _right) { return date.getYear() > _right.date.getYear(); }

		bool is_valid() const;

		template <typename T>
		bool hasFiled(const T& value) const { return false; };
		bool hasFiled(const std::string& _profession) const { return profession == _profession; };	

		static void show_titles();

	private:

		my_date::Date date;

	};
}

#endif // !DERIVED_WORKER_2_HPP