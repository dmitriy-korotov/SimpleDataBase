#pragma once
#ifndef DERIVED_WORKER_3_HPP
#define DERIVED_WORKER_3_HPP

#include "DerivedWorker2.hpp"



namespace lab_6
{
	class DerivedWorker3 : public lab_4::DerivedWorker2
	{
	public:

		friend std::istream& operator >> (std::istream& _in, DerivedWorker3& _right);
		friend std::ostream& operator << (std::ostream& _out, const DerivedWorker3& _right);
		friend std::ifstream& operator >> (std::ifstream& _fin, DerivedWorker3& _right);
		friend std::ofstream& operator << (std::ofstream& _fout, const DerivedWorker3& _right);



		DerivedWorker3() = default;

		bool is_valid() const;
		void set_job_title(const std::string _job_title) noexcept;
		const std::string& get_job_title() const noexcept;

		static void show_titles() noexcept;

	private:
	
		std::string job_title;

	};
}

#endif