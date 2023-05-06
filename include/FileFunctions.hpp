#pragma once
#ifndef FILE_FUNCTIONS_HPP
#define FILE_FUNCTIONS_HPP

#include "Settings.hpp"

#include <iostream>
#include <fstream>
#include <string>



#if CONTAINER == VECTOR
#include <vector>
#else
#include "Array.hpp"
#endif



namespace file_functs
{
	template <typename T>
	bool is_inclue(const std::string& name_file, const T& value)
	{
		bool is_include = false;
		std::string name;
		std::ifstream in(name_file, std::ios::in);

		if (in)
		{
			while (std::getline(in, name, ' '))
			{
				if (name == value) { is_include = true; break; }
			}
			in.close();
		}
		else
		{
			system("CLS");
			std::cout << DATABASE_ERROR << std::endl;
		}
		return is_include;
	}



	bool is_empty(const std::string& name_file)
	{
		std::ifstream in(name_file, std::ios::in);
		if (in.is_open())
		{
			std::string var;
			std::getline(in, var);

			bool empty = var == "" && in.eof();

			in.close();
			return empty;
		}
		else { throw std::exception("File not open"); }
	}



	void delete_word(const std::string& name_file, const std::string& word)
	{
		std::ifstream file_in(name_file, std::ios::in);
		if (file_in)
		{
			std::string temp_container;
#if CONTAINER == VECTOR
			std::vector<std::string> words;
#else
			my_array::Array<std::string> words;
#endif 

			while (!file_in.eof())
			{
				file_in >> temp_container;
				if (temp_container != word)	words.push_back(temp_container);
			}
			file_in.close();

			std::ofstream file_out(name_file, std::ios::out);

			if (file_out)
			{
#if CONTAINER == VECTOR
				for (int i = 0; i < words.size(); ++i) { file_out << ' ' + words[i]; }
#else
				for (int i = 0; i < words._size(); ++i) { file_out << ' ' + words[i]; }
#endif
				file_out.close();
			}
		}
	}



	void replace_word(const std::string& name_file, const std::string& old_word, const std::string& new_word)
	{
		std::ifstream file_in(name_file, std::ios::in);
		if (file_in)
		{
			std::string temp_container;
#if CONTAINER == VECTOR
			std::vector<std::string> words;
#else
			my_array::Array<std::string> words;
#endif 

			while (!file_in.eof())
			{
				file_in >> temp_container;
				if (temp_container != old_word)	words.push_back(temp_container);
				else { words.push_back(new_word); }
			}
			file_in.close();

			std::ofstream file_out(name_file, std::ios::out);

			if (file_out)
			{
#if CONTAINER == VECTOR
				for (int i = 0; i < words.size(); ++i) { file_out << ' ' + words[i]; }
#else
				for (int i = 0; i < words._size(); ++i) { file_out << ' ' + words[i]; }
#endif
				file_out.close();
			}
		}
	}
}

#endif // !FILE_FUNCTIONS_HPP