#pragma once
#ifndef DATA_BASE_INTERFACES_HPP
#define DATA_BASE_INTERFACES_HPP

#include "DataBaseFunct.hpp"
#include "CommonInterfaces.hpp"
#include "Settings.hpp"
#include "DataBase.hpp"
#include "FileFunctions.hpp"
#include "TableInterfaces.hpp"

#include <iostream>
#include <fstream>
#include <string>



namespace db_interface
{
	enum class EInterfaces : uint8_t
	{
		AddTable = 49,
		ShowTable = 50,
		MoveToTable = 51,
		DeleteTable = 52,
		Reload = 13,
		NotFound = 0
	};





	template <typename T>
	void add_table_interface(my_db::DataBase<T>& DB)
	{
		std::string name_table;

		db_functs::show_title("ƒŒ¡¿¬À≈Õ»≈ “¿¡À»÷€ ¬ ¡¿«” ƒ¿ÕÕ€’", WINDOW_WIDTH, '-');
		std::cout << "\n	¬¬≈ƒ»“≈ Õ¿«¬¿Õ»≈ “¿¡À»÷€:\t";	 std::cin >> name_table;

		if (file_functs::is_inclue(DB.get_path_to_file_with_table_names(), name_table))
		{
			db_functs::show_div_line('_', WINDOW_WIDTH);	std::cout << std::endl;
			db_functs::text_centering("ERROR:	ƒ¿ÕÕ¿ﬂ “¿¡À»÷¿ ”∆≈ —”Ÿ≈—“¬”≈“", WINDOW_WIDTH);
		}
		else
		{
			DB.add_table(name_table);

			std::cout << std::endl;
			db_functs::show_div_line('_', WINDOW_WIDTH);	std::cout << std::endl;
			db_functs::text_centering("“¿¡À»÷¿ ¡€À¿ ƒŒ¡¿¬À≈Õ¿ ¬ ¡¿«” ƒ¿ÕÕ€’", WINDOW_WIDTH);
		}

		db_functs::show_div_line('_', WINDOW_WIDTH);
		std::cout << "\n	Õ¿∆Ã»“≈ ENTER, ◊“Œ¡€ ¬≈–Õ”“‹—ﬂ Õ¿«¿ƒ\t\t";		char get = _getch();
	}





	template <typename T>
	void show_table_interface(const my_db::DataBase<T>& DB)
	{
		db_functs::show_title("¬€¬Œƒ ¬—≈’ “¿¡À»÷", WINDOW_WIDTH, '-');
		std::cout << "\n	Õ¿∆Ã»“≈ ENTER, ◊“Œ¡€ ”¬»ƒ≈“ —œ»—Œ  “¿¡À»÷\t\t";		char get = _getch();

		if (file_functs::is_empty(DB.get_path_to_file_with_table_names()))
		{
			std::cout << std::endl;
			db_functs::show_title("” ¬¿— Õ≈“ —Œ«ƒ¿ÕÕ€’ “¿¡À»÷", WINDOW_WIDTH, '~');
		}
		else
		{
			std::ifstream file_with_tables(DB.get_path_to_file_with_table_names(), std::ios::in);
			if (file_with_tables)
			{
				std::string name;

				std::cout << std::endl;
				db_functs::show_div_line('-', WINDOW_WIDTH);
				std::cout << "\n	¬¿ÿ» “¿¡À»÷€:\n\n";

				for (int i = 1; !file_with_tables.eof(); ++i)
				{
					file_with_tables >> name;
					std::cout << "............ " << i << " - " << name << std::endl;
				}
				std::cout << std::endl;		db_functs::show_div_line('-', WINDOW_WIDTH);
				file_with_tables.close();
			}
			else
			{
				system("CLS");
				std::cout << DATABASE_ERROR << std::endl;
			}
		}
		std::cout << "\n	Õ¿∆Ã»“≈ ENTER, ◊“Œ¡€ ¬≈–Õ”“‹—ﬂ Õ¿«¿ƒ\t\t";		get = _getch();
	}





	template <typename T>
	void go_to_table_interface(my_db::DataBase<T>& DB)
	{
		std::string name_table;

		db_functs::show_title("œ≈–≈’Œƒ   “¿¡À»÷≈", WINDOW_WIDTH, '-');
		std::cout << "\n	¬¬≈ƒ»“≈ Õ¿«¬¿Õ»≈ “¿¡À»÷€    Œ“Œ–Œ… ’Œ“»“≈ œ–≈…“»:\t\t";		std::cin >> name_table;
		
		if (file_functs::is_inclue(DB.get_path_to_file_with_table_names(), name_table))
		{
			system("CLS");
			table_interface::main_table_interface(DB, DB.get_ref_on_name_table(name_table));
			system("CLS");
		}
		else
		{
			std::cout << std::endl;
			db_functs::show_title("ƒ¿ÕÕŒ… “¿À»÷€ Õ≈ —”Ÿ≈—“¬”≈“", WINDOW_WIDTH, '~');
			std::cout << "\n	Õ¿∆Ã»“≈ ◊“Œ¡€ ENTER ¬≈–Õ”“‹—ﬂ Õ¿«¿ƒ:\t\t";		char get = _getch();
		}
	}





	template <typename T>
	void delete_table_interface(my_db::DataBase<T>& DB)
	{
		std::string name_table;

		db_functs::show_title("”ƒ¿À≈Õ»≈ “¿¡À»÷€", WINDOW_WIDTH, '-');
		std::cout << "\n	¬¬≈ƒ»“≈ Õ¿«¬¿Õ»≈ “¿¡À»÷€,  Œ“Œ–”ﬁ ’Œ“»“≈ ”ƒ¿À»“‹:\t";	 std::cin >> name_table;

		if (file_functs::is_inclue(DB.get_path_to_file_with_table_names(), name_table))
		{
			DB.delete_table(name_table);

			std::cout << std::endl;
			db_functs::show_div_line('_', WINDOW_WIDTH);	std::cout << std::endl;
			db_functs::text_centering("“¿¡À»÷¿ ¡€À¿ ”—œ≈ÿÕŒ ”ƒ¿À≈Õ¿", WINDOW_WIDTH);
		}
		else
		{
			db_functs::show_div_line('_', WINDOW_WIDTH);	std::cout << std::endl;
			db_functs::text_centering("ƒ¿ÕÕŒ… “¿¡À»÷€ Õ≈ —”Ÿ≈—“¬”≈“", WINDOW_WIDTH);
		}

		db_functs::show_div_line('_', WINDOW_WIDTH);
		std::cout << "\n	Õ¿∆Ã»“≈ ENTER, ◊“Œ¡€ ¬≈–Õ”“‹—ﬂ Õ¿«¿ƒ\t\t";		char get = _getch();
	}





	template<typename T>
	void main_data_base_interface(my_db::DataBase<T>& DB)
	{
		bool is_valid = false;
		bool end = false;
		char select_var = '0';

		while (true)
		{
			db_functs::show_title("¡¿«¿ ƒ¿ÕÕ€’ «¿œ”Ÿ≈Õ¿", WINDOW_WIDTH, '-');

			std::cout << "\n	¬€¡≈–»“≈ œ”Õ “ Ã≈Õﬁ:\n\n";
			std::cout << ".................ƒŒ¡¿¬»“‹ “¿¡À»÷” - 1.\n\n";
			std::cout << ".................œŒ—ÃŒ“–≈“‹ “¿¡À»÷€ - 2.\n\n";
			std::cout << ".................œ≈–≈…“»   “¿¡À»÷≈ - 3.\n\n";
			std::cout << ".................”ƒ¿À»“‹ “¿¡À»÷” - 4.\n\n";
			std::cout << ".................Œ¡ÕŒ¬»“‹ ¡¿«” ƒ¿ÕÕ€’ - ENTER.\n\n";
			std::cout << ".................ƒÀﬂ ¬€’Œƒ¿ »« ¡¿«€ ƒ¿ÕÕ€’ Õ¿∆Ã»“≈ - ESC.\n\n";

			db_functs::show_div_line('~', WINDOW_WIDTH);

			std::cout << "\n	¬¬≈ƒ»“≈ ÕŒÃ≈– œ”Õ “¿:\t";		select_var = _getche();		std::cout << "\n\n";

			if (select_var == static_cast<char>(common_interfaces::EKey::Escape)) 
			{ 
				end = true; break; 
			}

			switch (select_var)
			{
			case EInterfaces::AddTable:
				system("CLS");
				db_interface::add_table_interface(DB);	
				system("CLS");
				is_valid = true;
				break;

			case EInterfaces::ShowTable:
				system("CLS");
				db_interface::show_table_interface(DB);	
				system("CLS");
				is_valid = true;
				break;

			case EInterfaces::MoveToTable:
				system("CLS");
				db_interface::go_to_table_interface(DB); 
				system("CLS");
				is_valid = true;
				break;

			case EInterfaces::DeleteTable:
				system("CLS");
				db_interface::delete_table_interface(DB);
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
	}
}

#endif // DATA_BASE_INTERFACES_HPP