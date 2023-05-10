#include "ConsoleFunctions.hpp"



namespace console
{
	void setConsoleSize(uint16_t _width, uint16_t _height) noexcept
	{
		HANDLE hWnd = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD bufferSize = { static_cast<SHORT>(_width), static_cast<SHORT>(_height) };
		SetConsoleScreenBufferSize(hWnd, bufferSize);
		::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	}



	void setConsoleLanguage(const std::string _language) noexcept
	{
		setlocale(LC_ALL, _language.c_str());
	}
}