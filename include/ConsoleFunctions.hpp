#pragma once
#ifndef CONSOLE_FUNCTIONS_HPP
#define CONSOLE_FUNCTIONS_HPP

#include <iostream>
#include <Windows.h>



namespace console
{
	void setConsoleSize(uint16_t _width, uint16_t _height) noexcept;
	
	void setConsoleLanguage(const std::string _language) noexcept;
}

#endif // !CONSOLE_FUNCTIONS_HPP
