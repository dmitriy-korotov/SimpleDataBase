#pragma once
#ifndef DERIVED_WORKER_1_HPP
#define DERIVED_WORKER_1_HPP

#include "IWorker.hpp"

#include <fstream>



namespace lab_3
{
	class DerivedWorker1 : public lab_4::IWorker
	{
	public:

		friend std::istream& operator >> (std::istream& _in, DerivedWorker1& _right);
		friend std::ostream& operator << (std::ostream& _out, const DerivedWorker1& _right);
		friend std::ifstream& operator >> (std::ifstream& _fin, DerivedWorker1& _right);
		friend std::ofstream& operator << (std::ofstream& _fout, const DerivedWorker1& _right);



		DerivedWorker1() = default;
		DerivedWorker1(const DerivedWorker1&) = default;
		DerivedWorker1& operator=(const DerivedWorker1&) = default;
		DerivedWorker1(DerivedWorker1&&) = default;
		DerivedWorker1& operator=(DerivedWorker1&&) = default;
		~DerivedWorker1() = default;



		explicit DerivedWorker1(const Man& person);
		DerivedWorker1(const std::string& _name, const std::string& _surname, const std::string& _profession,
			   unsigned int _department_number, float _salary);

		bool operator==(const Man& _right);
		bool operator>(const DerivedWorker1& _right) const { return salary > _right.salary; };
		bool operator<(const DerivedWorker1& _right) const { return salary < _right.salary; };

		void set_department_number(unsigned int _department_number);
		void set_salary(float _salary);

		unsigned int get_department_number() const { return department_number; }
		float get_salary() const { return salary; }

		template <typename T>
		bool hasFiled(const T& value) const { return false; }
		
		bool hasFiled(unsigned int _departament_number) const { return department_number == _departament_number; }
		bool is_valid() const;
	
		static void show_titles();

	private:

		unsigned int department_number = 0;
		float salary = 0;

	};
}

#endif // !DERIVED_WORKER_1_HPP