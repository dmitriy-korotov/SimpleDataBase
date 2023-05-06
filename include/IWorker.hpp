#pragma once
#ifndef I_WORKER_HPP
#define I_WORKER_HPP

#include "Man.hpp"

#include <fstream>



namespace lab_4
{
	class IWorker
	{
	public:

		friend std::istream& operator >> (std::istream& _in, IWorker& _right);
		friend std::ostream& operator << (std::ostream& _out, const IWorker& _right);
		friend std::ifstream& operator >> (std::ifstream& _fin, IWorker& _right);
		friend std::ofstream& operator << (std::ofstream& _fout, const IWorker& _right);



		IWorker() = default;
		IWorker(const IWorker&) = default;
		IWorker& operator=(const IWorker&) = default;
		~IWorker() = default;

		explicit IWorker(const lab_3::Man& _person) : person(_person) {};
		IWorker(const std::string& _name, const std::string& _surname, const std::string& _profession)
			: person(_name, _surname)
			, profession(_profession)
		{ }

		bool operator == (const lab_3::Man& _right) { return person == _right; }

		bool profession_is_equal(const std::string& _profession) const { return profession == _profession; }

	protected:

		lab_3::Man person;
		std::string profession;

	};
}

#endif // !I_WORKER_HPP