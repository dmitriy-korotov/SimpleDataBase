#pragma once
#ifndef TABLE_INTERFACES_HPP
#define TABLE_INTERFACES_HPP

#include "Settings.hpp"
#include "DataBase.hpp"
#include "CommonInterfaces.hpp"
#include "DataBaseFunct.hpp"
#include "DerivedWorker1.hpp"
#include "DerivedWorker2.hpp"
#include "DerivedWorker3.hpp"
#include "Date.hpp"
#include "Person.hpp"

#include <iostream>
#include <typeinfo>
#include <string>



namespace table_interface
{
	enum class EInterfaces : uint8_t
	{
		AddTable = 49,
		ShowRecordsOfTable = 50,
		RenameTable = 51,
		DeleteRecordOfTable = 52,
		SortRecordsOfTable = 53,
		FindProductionByPersonality = 54,
		FilterRecordsByField = 55,
		Reload = 13,
		NotFound = 0
	};





	template <typename T>
	void add_table_interface(my_db::DataBase<T>& DB, const std::string& name_table) noexcept
	{
		db_functs::show_title(("ƒŒ¡¿¬À≈Õ»≈ «¿œ»—» ¬ “¿¡À»÷”:\t" + name_table).c_str(), WINDOW_WIDTH, '-');
		std::cout << "\n	Õ¿∆Ã»“≈ ENTER, ◊“Œ¡€ Õ¿◊¿“‹ ƒŒ¡¿¬Àﬂ“‹ «¿œ»—‹\t";	char get = _getche();		std::cout << "\n\n";
		db_functs::show_div_line('~', WINDOW_WIDTH);	std::cout << std::endl;

		T new_record{};
		std::cin >> new_record;

		if (new_record.is_valid())
		{
			try
			{
				DB.add_record_to_table(name_table, new_record);
				db_functs::show_title("«¿œ»—‹ ¡€À¿ ƒŒ¡¿¬À≈Õ¿ ¬ ¡¿«” ƒ¿ÕÕ€’", WINDOW_WIDTH, '-');
			}
			catch (const std::exception& _ex)
			{
				db_functs::show_title(_ex.what(), WINDOW_WIDTH, '~');
			}
		}
		else
		{
			db_functs::show_title("ƒ¿ÕÕ€≈ «¿œŒÀÕ≈Õ€ Õ≈  Œ––≈ “ÕŒ, «¿œ»—‹ Õ≈ ¡€À¿ ƒŒ¡¿¬À≈Õ¿", WINDOW_WIDTH, '-');
		}
		std::cout << "\n	Õ¿∆Ã»“≈ ENTER, ◊“Œ¡€ ¬≈–Õ”“‹—ﬂ\t";		get = _getche();
	}





	template <typename T>
	void show_records_of_table_interface(my_db::DataBase<T>& DB, const std::string& name_table) noexcept
	{
		db_functs::show_title("¬€¬Œƒ ¬—≈’ «¿œ»—≈… ¬ “¿¡À»÷≈", WINDOW_WIDTH, '-');
		std::cout << std::endl;
		db_functs::text_centering(("“¿¡À»÷¿:   " + name_table).c_str(), WINDOW_WIDTH);	std::cout << std::endl;

		try
		{
			if (!DB.table_is_empty(name_table))
			{
				db_functs::show_div_line('~', WINDOW_WIDTH);
				DB.show_table(name_table);
			}
			else
			{
				db_functs::show_title("¬ “¿¡À»÷≈ Õ≈“ «¿œ»—≈…", WINDOW_WIDTH, '~');
			}
		}
		catch (const std::exception& _ex)
		{
			db_functs::show_title(_ex.what(), WINDOW_WIDTH, '~');
		}
		std::cout << "\n\n	Õ¿∆Ã»“≈ ENTER, ◊“Œ¡€ ¬≈–Õ”“‹—ﬂ\t";		char get = _getch();
	}

	



	template <typename T>
	void rename_table_interface(my_db::DataBase<T>& DB, const std::string& name_table) noexcept
	{
		std::string new_name_table;

		db_functs::show_title("œ≈–≈»Ã≈ÕŒ¬¿Õ»≈ “¿¡À»÷€", WINDOW_WIDTH, '-');
		std::cout << "\n	¬¬≈ƒ»“≈ ÕŒ¬Œ≈ Õ¿«¬¿Õ»≈ “¿¡À»÷€\t\t";		std::cin >> new_name_table;

		try 
		{
			DB.rename_table(name_table, new_name_table);
		}
		catch (const std::exception& _ex)
		{
			db_functs::show_title(_ex.what(), WINDOW_WIDTH, '~');
		}

		std::cout << "\n\n";
		db_functs::show_title("Õ¿«¬¿Õ»≈ ¡€ÀŒ ”—œ≈ÿÕŒ »«Ã≈Õ≈ÕŒ", WINDOW_WIDTH, '~');
		std::cout << "\n\n	Õ¿∆Ã»“≈ ENTER, ◊“Œ¡€ ¬≈–Õ”“‹—ﬂ\t\t";		char get = _getch();
	}





	template <typename T>
	void delete_record_of_table_interface(my_db::DataBase<T>& DB, const std::string& name_table) noexcept
	{
		size_t number_of_record;

		db_functs::show_title("”ƒ¿À≈Õ»≈ «¿œ»—» ¬ “¿¡À»÷≈", WINDOW_WIDTH, '-');
		std::cout << "\n	¬¬≈ƒ»“≈ ÕŒÃ≈– «¿œ»—»,  Œ“Œ–”ﬁ ¬€ ’Œ“»“≈ ”ƒ¿À»“‹:\t\t";		std::cin >> number_of_record;
		std::cout << "\n\n";
		
		try
		{
			if (DB.delete_record_of_table(name_table, number_of_record))
			{
				db_functs::show_title("«¿œ»—‹ ¬ “¿¡À»÷≈ ¡€À¿ ”—œ≈ÿÕŒ ”ƒ¿À≈Õ¿", WINDOW_WIDTH, '~');
			}
			else
			{
				db_functs::show_title("Õ≈ ”ƒ¿ÀŒ—‹ ”ƒ¿À»“‹ «¿œ»—‹", WINDOW_WIDTH, '~');
			}
		}
		catch (const std::exception& _ex)
		{
			db_functs::show_title(_ex.what(), WINDOW_WIDTH, '~');
		}

		std::cout << "\n\n	Õ¿∆Ã»“≈ ENTER, ◊“Œ¡€ ¬≈–Õ”“‹—ﬂ\t\t";		char get = _getch();
	}

	



	template <typename T>
	void sort_records_of_table_interface(my_db::DataBase<T>& DB, const std::string& name_table) noexcept
	{
		char type_sort;

		db_functs::show_title("—Œ–“»–Œ¬ ¿ «¿œ»—≈… ¬ “¿¡À»÷≈", WINDOW_WIDTH, '-');
		std::cout << "\n	¬€¡≈–»“≈ ¬»ƒ —Œ–“»–Œ¬ » S/R (S - Œ¡€◊Õ¿ﬂ, R - ¬ Œ¡–¿“ÕŒÃ œŒ–ﬂƒ ≈):\t";		std::cin >> type_sort;
		rewind(stdin);

		try
		{
			if (type_sort == 's' || type_sort == 'S')
			{
				DB.sort_records_of_table(name_table);
				std::cout << "\n\n";
				db_functs::show_title("«¿œ»—» ¡€À» ”—œ≈ÿÕŒ Œ—Œ–“»–Œ¬¿Õ€", WINDOW_WIDTH, '~');
			}
			else if (type_sort == 'r' || type_sort == 'R')
			{
				DB.sort_records_of_table(name_table, true);
				std::cout << "\n\n";
				db_functs::show_title("«¿œ»—» ¡€À» ”—œ≈ÿÕŒ Œ—Œ–“»–Œ¬¿Õ€", WINDOW_WIDTH, '~');
			}
			else
			{
				std::cout << "\n\n";
				db_functs::show_title("Õ≈“ ƒ¿ÕÕŒ√Œ ¬»ƒ¿ —Œ–“»–Œ¬ »", WINDOW_WIDTH, '~');
			}
		}
		catch (const std::exception& _ex)
		{
			db_functs::show_title(_ex.what(), WINDOW_WIDTH, '~');
		}

		std::cout << "\n\n	Õ¿∆Ã»“≈ ENTER, ◊“Œ¡€ ¬≈–Õ”“‹—ﬂ Õ¿«¿ƒ\t\t";		char get = _getch();
	}





	template <typename T>
	void find_production_by_personality(my_db::DataBase<T>& DB, const std::string& name_table) noexcept
	{
		lab_3::Person person;

		db_functs::show_title("œŒ»—  –¿¡Œ“Õ» ¿ œŒ »Ã≈Õ» » ‘¿Ã»À»»", WINDOW_WIDTH, '-');
		std::cout << std::endl;		std::cin >> person;

		try
		{
			if (!DB.find_record_by_field(name_table, person))
			{
				std::cout << "\n\n";
				db_functs::show_title("–¿¡Œ“Õ»  Õ≈ ¡€À Õ¿…ƒ≈Õ", WINDOW_WIDTH, '~');
			}
		}
		catch (const std::exception& _ex)
		{
			db_functs::show_title(_ex.what(), WINDOW_WIDTH, '~');
		}

		std::cout << "\n\n	Õ¿∆Ã»“≈ ENTER, ◊“Œ¡€ ¬≈–Õ”“‹—ﬂ Õ¿«¿ƒ\t\t";		char get = _getch();
	}





	inline void filter_records_by_dapartament_number_interface(my_db::DataBase<lab_3::DerivedWorker1>& DB, const std::string& name_table) noexcept
	{
		unsigned int departament_number = -1;

		db_functs::show_title("‘»À‹“– «¿œ»—≈… œŒ ÕŒÃ≈–” Œ“ƒ≈À¿", WINDOW_WIDTH, '-');
		std::cout << "\n	¬¬≈ƒ»“≈ ÕŒÃ≈– Œ“ƒ≈À¿:\t\t";		std::cin >> departament_number;
		while (std::cin.fail())
		{
			std::cin.clear();
			rewind(stdin);
			std::cout << "\n	¬¬≈ƒ»“≈  Œ––≈ “Õ€… ÕŒÃ≈– Œ“ƒ≈À¿:\t\t";		std::cin >> departament_number;
		}
		std::cout << "\n\n";

		try
		{
			DB.show_filter_records_of_table(name_table,
				[&](const lab_3::DerivedWorker1& _worker)
				{
					return _worker.equalDepartamentNumber(departament_number);
				});
		}
		catch (const std::exception& _ex)
		{
			db_functs::show_title(_ex.what(), WINDOW_WIDTH, '~');
		}

		std::cout << "\n\n	Õ¿∆Ã»“≈ ENTER, ◊“Œ¡€ ¬≈–Õ”“‹—ﬂ Õ¿«¿ƒ\t\t";		char get = _getch();
	}
	




	inline void filter_records_by_profession_interface(my_db::DataBase<lab_4::DerivedWorker2>& DB, const std::string& name_table) noexcept
	{
		std::string profession;

		db_functs::show_title("‘»À‹“– «¿œ»—≈… œŒ Õ¿«¬¿Õ»ﬁ œ–Œ‘≈—»»", WINDOW_WIDTH, '-');
		std::cout << "\n	¬¬≈ƒ»“≈ Õ¿«¬¿Õ»≈ œ–Œ‘≈—»»:\t\t";		std::cin >> profession;
		std::cout << "\n\n";
		
		try
		{
			DB.show_filter_records_of_table(name_table,
				[&](const lab_4::DerivedWorker2& _worker)
				{
					return _worker.equalProfession(profession);
				});
		}
		catch (const std::exception& _ex)
		{
			db_functs::show_title(_ex.what(), WINDOW_WIDTH, '~');
		}

		std::cout << "\n\n	Õ¿∆Ã»“≈ ENTER, ◊“Œ¡€ ¬≈–Õ”“‹—ﬂ Õ¿«¿ƒ\t\t";		char get = _getch();
	}





	inline void filter_records_by_date(my_db::DataBase<lab_6::DerivedWorker3>& DB, const std::string& name_table) noexcept
	{
		my_date::Date date;

		db_functs::show_title("‘»À‹“– «¿œ»—≈… ƒÀ»“≈À‹ÕŒ—“» –¿¡Œ“€ (–¿¡Œ“¿À» ¡ŒÀ≈≈ 10 À≈“)", WINDOW_WIDTH, '-');
		std::cout << "\n	¬¬≈ƒ»“≈ “≈ Ÿ”ﬁ ƒ¿“”:\t\t";		std::cin >> date;
		std::cout << "\n\n";

		try
		{
			DB.show_filter_records_of_table(name_table,
				[&](const lab_6::DerivedWorker3& _worker)
				{
					return my_date::Date::castToYears(_worker.getDate().difference(date)) > 10;
				});
		}
		catch (const std::exception& _ex)
		{
			db_functs::show_title(_ex.what(), WINDOW_WIDTH, '~');
		}

		std::cout << "\n\n	Õ¿∆Ã»“≈ ENTER, ◊“Œ¡€ ¬≈–Õ”“‹—ﬂ Õ¿«¿ƒ\t\t";		char get = _getch();
	}





	template <typename T>
	void main_table_interface(my_db::DataBase<T>& DB, const std::string& name_table) noexcept
	{
		short select_var;
		bool end = false, is_valid = false;

		while (!is_valid)
		{
			while (true)
			{
				db_functs::show_title(("“¿¡À»÷¿:\t" + name_table).c_str(), WINDOW_WIDTH, '-');

				std::cout << "\n	¬€¡≈–»“≈ œ”Õ “ Ã≈Õﬁ:\n\n";
				std::cout << ".................ƒŒ¡¿¬»“‹ «¿œ»—‹ ¬ “¿¡À»÷” - 1.\n\n";
				std::cout << ".................œŒ—ÃŒ“–≈“‹ «¿œ»—» ¬ “¿¡À»÷≈ - 2.\n\n";
				std::cout << ".................œ≈–≈»Ã≈ÕŒ¬¿“‹ “¿¡À»÷” - 3.\n\n";
				std::cout << ".................”ƒ¿À»“‹ «¿œ»—‹ ¬ “¿¡À»÷≈ - 4.\n\n";
				std::cout << ".................Œ“—Œ–“»–Œ¬¿“‹ «¿œ»—» ¬ “¿¡À»÷≈ - 5.\n\n";
				std::cout << ".................Õ¿…“» –¿¡Œ“Õ» ¿ - 6.\n\n";
				if (typeid(T) == typeid(lab_4::DerivedWorker2))
				{
					std::cout << ".................œŒ—ÃŒ“–≈“‹ Œ“‘»À‹“–Œ¬¿ÕÕ€≈ «¿œ»—» œŒ Õ¿«¬¿Õ»ﬁ œ–Œ‘≈——»» - 7.\n\n";
				}
				else if (typeid(T) == typeid(lab_3::DerivedWorker1))
				{
					std::cout << ".................œŒ—ÃŒ“–≈“‹ Œ“‘»À‹“–Œ¬¿ÕÕ€≈ «¿œ»—» œŒ ÕŒÃ≈–” Œ“ƒ≈À¿ - 7.\n\n";
				}
				else if (typeid(T) == typeid(lab_6::DerivedWorker3))
				{
					std::cout << ".................œŒ—ÃŒ“–≈“‹ Œ“‘»À‹“–Œ¬¿ÕÕ€≈ «¿œ»—» œŒ ƒ¿“≈ œ–»Õﬂ“»ﬂ Õ¿ –¿¡Œ“” - 7.\n\n";
				}
				std::cout << ".................Œ¡ÕŒ¬»“‹ “¿¡À»÷” - ENTER.\n\n";
				std::cout << ".................ƒÀﬂ “Œ√Œ, ◊“Œ¡€ ¬€…“» »« “¿¡À»÷€ Õ¿∆Ã»“≈  - ESC.\n\n";

				db_functs::show_div_line('~', WINDOW_WIDTH);
				std::cout << "\n	¬¬≈ƒ»“≈ ÕŒÃ≈– œ”Õ “¿:\t";		select_var = _getche();		std::cout << "\n\n";

				if (select_var == static_cast<char>(common_interfaces::EKey::Escape))
				{
					end = true;
					break; 
				}

				switch (select_var)
				{
				case EInterfaces::AddTable:
					system("CLS");
					add_table_interface(DB, name_table);	
					system("CLS");
					is_valid = true;
					break;

				case EInterfaces::ShowRecordsOfTable:
					system("CLS");
					show_records_of_table_interface(DB, name_table);
					system("CLS");
					is_valid = true;
					break;

				case EInterfaces::RenameTable:
					system("CLS");
					rename_table_interface(DB, name_table);		
					system("CLS");
					is_valid = true;
					break;

				case EInterfaces::DeleteRecordOfTable:
					system("CLS");
					delete_record_of_table_interface(DB, name_table);	 
					system("CLS");
					is_valid = true;
					break;

				case EInterfaces::SortRecordsOfTable:
					system("CLS");
					sort_records_of_table_interface(DB, name_table);	 
					system("CLS");
					is_valid = true;
					break;

				case EInterfaces::FindProductionByPersonality:
					system("CLS");
					find_production_by_personality(DB, name_table);	
					system("CLS");
					is_valid = true;
					break;

				case EInterfaces::FilterRecordsByField:
					system("CLS");
					if (typeid(T) == typeid(lab_3::DerivedWorker1))
					{
						filter_records_by_dapartament_number_interface(reinterpret_cast<my_db::DataBase<lab_3::DerivedWorker1>&>(DB), name_table);	 
					}
					else if (typeid(T) == typeid(lab_4::DerivedWorker2))
					{
						filter_records_by_profession_interface(reinterpret_cast<my_db::DataBase<lab_4::DerivedWorker2>&>(DB), name_table);
					}
					else if (typeid(T) == typeid(lab_6::DerivedWorker3))
					{
						filter_records_by_date(reinterpret_cast<my_db::DataBase<lab_6::DerivedWorker3>&>(DB), name_table);
					}
					system("CLS");
					is_valid = true;
					break;

				case EInterfaces::Reload:
					system("CLS");		
					break;

				default:
					system("CLS");
					common_interfaces::not_found_interface();	
					system("CLS");
					break;
				}
			}

			if (end) break;
		}
	}
}

#endif // !TABLE_INTERFACES_HPP