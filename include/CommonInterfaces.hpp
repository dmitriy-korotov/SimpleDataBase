#pragma once
#ifndef COMMON_INTERFACES_HPP
#define COMMON_INTERFACES_HPP

#include "DataBaseFunct.hpp"
#include "Settings.hpp"

#include <iostream>
#include <conio.h>



namespace common_interfaces
{
	enum class EKey : uint8_t
	{
		Escape = 27
	};



	inline void not_found_interface() noexcept
	{
		db_functs::show_title("ERROR:	ббед╗ммнцн бюлх осмйрю ме ясыеярбсер\n", WINDOW_WIDTH, '*');
		std::cout << "\n	мюфлхре ENTER, врнаш бепмсрэяъ мюгюд\t";
		char get = _getch();
	}
}

#endif // !COMMON_INTERFACES_HPP