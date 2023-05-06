#include "Settings.hpp"
#include "CommonInterfaces.hpp"
#include "DataBaseInterfaces.hpp"
#include "DataBaseFunct.hpp"
#include "DataBase.hpp"

#include "DerivedWorker1.hpp"
#include "DerivedWorker2.hpp"

#include <iostream>
#include <conio.h>
#include <iomanip>



#if MEMORY_CHECK == ON
#include "MemoryLeaksDebug.hpp"
#endif



enum class EMainDataBaseInterfaces : uint8_t
{
	DerivedWorker1 = 49,
	DerivedWorker2 = 50,
	Reload = 13,
	NotFound = 0
};



int main(int argc, char** argv)
{
	setlocale(LC_ALL, "ru-RU");

#if DEBUG == OFF
#if MEMORY_CHECK == ON
	{
#endif // MEMORY_CHECK

		my_db::DataBase<lab_3::DerivedWorker1>::set_executable_path(argv[0]);
		my_db::DataBase<lab_4::DerivedWorker2>::set_executable_path(argv[0]);
		my_db::DataBase<lab_3::DerivedWorker1> DB_1("res/DataBaseTables/names_of_tables.txt", "res/DataBaseTables/Tables/Worker1/");
		my_db::DataBase<lab_4::DerivedWorker2> DB_2("res/DataBaseTables/names_of_tables_2.txt", "res/DataBaseTables/Tables/Worker2/");
		
		char select_var = '0';
		bool is_valid = false, end = false;

		while (!is_valid)
		{
			db_functs::show_title("����� ���� ������", WINDOW_WIDTH, '-');
			std::cout << "\n\t\t�������� ���� ������:";
			std::cout << "\n\n\t1..............................�������� 1";
			std::cout << "\n\n\t2..............................�������� 2";
			std::cout << "\n\n";

			db_functs::show_div_line('~', WINDOW_WIDTH);
			std::cout << "\n\t������� ����� ������:\t\t";	select_var = _getch();		std::cout << std::endl;

			switch (select_var)
			{
			case static_cast<int>(common_interfaces::EKey::Escape):
				end = true;
				break;

			case static_cast<int>(EMainDataBaseInterfaces::DerivedWorker1):
				system("CLS");
				db_interface::main_data_base_interface(DB_1);
				system("CLS");
				break;

			case static_cast<int>(EMainDataBaseInterfaces::DerivedWorker2):
				system("CLS");
				db_interface::main_data_base_interface(DB_2);
				system("CLS");
				break;

			case static_cast<int>(EMainDataBaseInterfaces::Reload):
				system("CLS");
				break;
					
			default:
				system("CLS");
				common_interfaces::not_found_interface();
				system("CLS");
				break;
			}

			if (end) break;
		}

#if MEMORY_CHECK == ON
	}
	std::cout << ".................................................Memory leaks: " << MemoryDebug::getSizeMemoryLeaks() << " bytes" << std::endl;
#endif // MEMORY_CHECK

#endif // DEBUG

	return 0;
}