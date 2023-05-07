#pragma once
#ifndef DATA_BASE_FUNCT_HPP
#define DATA_BASE_FUNCT_HPP

#include "Array.hpp"

#include <iostream>
#include <vector>
#include <memory>



namespace db_functs
{
	void text_centering(const char* text, size_t size) noexcept;
	void show_div_line(const char symbol, size_t size) noexcept;
	void show_title(const char* text, size_t szie, const char symbol_div = '#') noexcept;



	template <typename T>
	void sort(std::vector<T>& conteiner, bool reverse = false) noexcept
	{
		for (size_t i = 0; i < conteiner.size(); ++i)
		{
			T insert_var = conteiner[i];
			size_t index_insert = i;
			for (size_t j = i; j < conteiner.size(); ++j)
			{
				if (reverse)
				{
					if (*conteiner[j] > *insert_var) { insert_var = conteiner[j]; index_insert = j; }
				}
				else
				{
					if (*conteiner[j] < *insert_var) { insert_var = conteiner[j]; index_insert = j; }
				}
			}
			conteiner[index_insert] = conteiner[i];
			conteiner[i] = insert_var;
		}
	}



	template <typename T>
	void sort(my_array::Array<T>& conteiner, bool reverse = false) noexcept
	{
		for (size_t i = 0; i < conteiner._size(); ++i)
		{
			T insert_var = conteiner[i];
			size_t index_insert = i;
			for (size_t j = i; j < conteiner._size(); ++j)
			{
				if (reverse)
				{
					if (*conteiner[j] > *insert_var) { insert_var = conteiner[j]; index_insert = j; }
				}
				else
				{
					if (*conteiner[j] < *insert_var) { insert_var = conteiner[j]; index_insert = j; }
				}
			}
			conteiner[index_insert] = conteiner[i];
			conteiner[i] = insert_var;
		}
	}
}

#endif // !DATA_BASE_FUNCT_H