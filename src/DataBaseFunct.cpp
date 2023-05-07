#include "DataBaseFunct.hpp"



namespace db_functs
{
	void text_centering(const char* text, size_t size) noexcept
	{
		const size_t text_length = strlen(text);
		const size_t space_length = (size - text_length) / 2;

		for (int i = 0; i < space_length; i++)
		{
			printf(" "); 
		}
		printf("%s\n", text);
	}



	void show_div_line(const char symbol, size_t size) noexcept
	{
		for (int i = 0; i < size; i++) { 
			printf("%c", symbol); 
		}
		printf("\n");
	}



	void show_title(const char* text, size_t size, const char symbol_div) noexcept
	{
		show_div_line(symbol_div, size);
		text_centering(text, size);
		show_div_line(symbol_div, size);
	}
}