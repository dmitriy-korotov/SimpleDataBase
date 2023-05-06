#pragma once
#ifndef DATA_BASE_HPP
#define DATA_BASE_HPP

#include "Settings.hpp"
#include "FileFunctions.hpp"
#include "DataBaseFunct.hpp"

#include <iostream>
#include <fstream>
#include <memory>
#include <iomanip>
#include <filesystem>



#if CONTAINER == VECTOR
#include <vector>
#else
#include "Array.hpp"
#endif



namespace my_db
{
	template <typename T>
	class DataBase
	{
	public:

		DataBase(const std::string& path_to_file_with_table_names, const std::string& path_to_tables);
		DataBase(const DataBase&) = delete;
		DataBase(DataBase&&) = delete;
		DataBase& operator=(const DataBase&) = delete;
		DataBase& operator=(DataBase&&) = delete;



		static void set_executable_path(const std::string& _path_to_exe);

		

		const std::string& get_ref_on_name_table(const std::string& name_table);
		const std::string& get_path_to_file_with_table_names() const;
		
		void add_table(const std::string& name_table);
		void rename_table(const std::string& old_name_table, const std::string& new_name_table);
		void add_record_to_table(const std::string& name_table, const T& record);
		bool delete_record_of_table(const std::string& name_table, const size_t& number_of_record);
		void sort_records_of_table(const std::string& name_table, bool reverse = false);
		void delete_table(const std::string& name_table);
		void show_table(const std::string& name_table);
		bool table_is_empty(const std::string& name_table);
		void show_filter_records_of_table(const std::string& name_table, const std::string& profession);

		template <typename U>
		bool find_record_by_field(const std::string& name_table, const U& value);

		template <typename U>
		void show_filter_records_of_table(const std::string& name_table, const U& value);

	protected:

		class Table
		{
		private:

			size_t amount_records = 0;
			std::string path_to_file_with_table_names;
			std::string table_name;
			std::string folder_width_tables;
#if CONTAINER == MY_ARRAY
			my_array::Array<std::shared_ptr<T>> table_records;
#else
			std::vector<std::shared_ptr<T>> table_records;
#endif

		private:

			void __write_name_to_file(const std::string& file_name, const std::string& name) const;
			void __read_records_from_file(const std::string& file_name);
			void __write_record_to_file(const T& record) const;
			void __delete_record_in_file(const std::string& name_file, const size_t& number_of_record);

		public:

			Table() = default;
			Table(const Table&) = default;
			Table& operator=(const Table&) = default;
			Table(Table&&) = default;
			Table& operator=(Table&&) = default;
			Table(const std::string& table_name, const std::string& path_to_file_with_table_names, const std::string& path_to_tables);
			~Table();



			const std::string& get_name_table() const;
			const size_t& get_amount_records() const;

			bool empty() const;
			void rename_table(const std::string& new_name);
			void add_record(const T& record);
			bool delete_record(const size_t number_of_record);
			void destroy();
			void show_table();
			void sort_records(const bool reverse = false);

			template <typename U>
			bool show_finded_record(const U& value);

			template <typename U>
			void show_filter_by_field(const U& value);
		};


	private:

		static void createFile(const std::string& _path);
		Table& __find_table(const std::string& name_table);

	private:

		static size_t amount_tables;
		static std::string path_to_exe;

	private:

#if CONTAINER == MY_ARRAY
		my_array::Array<Table> tables;
#else
		std::vector<Table> tables;
#endif
		std::string file_with_name_tabels;		
		std::string folder_width_tables;

	};





	template <typename T> size_t DataBase<T>::amount_tables = 0;
	template <typename T> std::string DataBase<T>::path_to_exe;



	////////////////////////////////////////////////////////
	//                      DATABASE
	////////////////////////////////////////////////////////

	

	template <typename T>
	void DataBase<T>::set_executable_path(const std::string& _path_to_exe)
	{
		path_to_exe = _path_to_exe.substr(0, _path_to_exe.find_last_of("\\/"));
	}

	

	template <typename T>
	DataBase<T>::DataBase(const std::string& path_to_file_with_table_names, const std::string& path_to_tables)
	{
		file_with_name_tabels = path_to_exe + '/' + path_to_file_with_table_names;
		folder_width_tables = path_to_exe + '/' + path_to_tables;

		std::error_code _error;
		if (!std::filesystem::exists(file_with_name_tabels, _error))
		{
			try
			{
				createFile(file_with_name_tabels);
			}
			catch (const std::exception& _ex)
			{
				std::cerr << _ex.what() << std::endl;
			}
		}

		std::ifstream file_with_tables(file_with_name_tabels, std::ios::in);

		if (file_with_tables.is_open())
		{
			if (!file_functs::is_empty(file_with_name_tabels))
			{
				std::string name_table;
				while (!file_with_tables.eof())
				{
					file_with_tables >> name_table;
					this->tables.push_back(Table(name_table, file_with_name_tabels, folder_width_tables));
				}
			}
			file_with_tables.close();
		}
		else
		{
			system("CLS");
			std::cout << DATABASE_ERROR << std::endl;
		}
	}



	template <typename T>
	void DataBase<T>::createFile(const std::string& _path)
	{
		size_t sep_index = _path.find_last_of("\\/");
		std::error_code _error;
		std::filesystem::path _directory_path = _path.substr(0,  sep_index);
		std::filesystem::create_directories(_directory_path);

		std::ofstream create_file(_path);
		if (create_file.is_open())
		{
			create_file.close();
		}
		else
		{
			throw std::exception(("ERROR: Can't create file: " + _path).c_str());
		}
	}


	
	template <typename T>
	DataBase<T>::template Table& DataBase<T>::__find_table(const std::string& name_table)
	{
#if CONTAINER == VECTOR
		for (int index = 0; index < tables.size(); ++index)
#else
		for (int index = 0; index < tables._size(); ++index)
#endif
		{
			if (tables[index].get_name_table() == name_table) { return tables[index]; }
		}
		throw std::exception("Table not found");
	}

	

	template <typename T>
	const std::string& DataBase<T>::get_ref_on_name_table(const std::string& name_table)
	{
		Table& table = __find_table(name_table);
		return table.get_name_table();
	}



	template <typename T>
	const std::string& DataBase<T>::get_path_to_file_with_table_names() const
	{
		return file_with_name_tabels;
	}



	template <typename T>
	void DataBase<T>::add_table(const std::string& name_table)
	{
		Table new_table(name_table, file_with_name_tabels, folder_width_tables);
		this->tables.push_back(new_table);
	}



	template <typename T>
	bool DataBase<T>::delete_record_of_table(const std::string& name_table, const size_t& number_of_record)
	{
		Table& table = __find_table(name_table);
		return table.delete_record(number_of_record);
	}



	template <typename T>
	void DataBase<T>::sort_records_of_table(const std::string& name_table, bool reverse)
	{
		Table& table = __find_table(name_table);
		table.sort_records(reverse);
	}



	template <typename T>
	void DataBase<T>::rename_table(const std::string& old_name_table, const std::string& new_name_table)
	{
		Table& table = __find_table(old_name_table);
		table.rename_table(new_name_table);
	}



	template <typename T>
	void DataBase<T>::add_record_to_table(const std::string& name_table, const T& record)
	{
		Table& table = __find_table(name_table);
		table.add_record(record);
	}



	template <typename T>
	void DataBase<T>::delete_table(const std::string& name_table)
	{
		int index = 0;
#if CONTAINER == VECTOR
		for (; index < tables.size(); ++index)
#else
		for (; index < tables._size(); ++index)
#endif
		{
			if (tables[index].get_name_table() == name_table)
			{
				tables[index].destroy();
				break;
			}
		}
#if CONTAINER == VECTOR
		auto it = tables.begin();
		tables.erase(it + index);
#else
		tables.erase(index);
#endif
	}



	template <typename T>
	void DataBase<T>::show_table(const std::string& name_table)
	{
		Table table = this->__find_table(name_table);
		table.show_table();
	}



	template <typename T>
	bool DataBase<T>::table_is_empty(const std::string& name_table)
	{
		Table& table = __find_table(name_table);
		return table.empty();
	}



	template <typename T>
	void DataBase<T>::show_filter_records_of_table(const std::string& name_table, const std::string& profession)
	{
		Table& table = __find_table(name_table);
		table.show_filter_by_field(profession);
	}



	template <typename T>
	template <typename U>
	bool DataBase<T>::find_record_by_field(const std::string& name_table, const U& person)
	{
		Table& table = __find_table(name_table);
		return table.show_finded_record(person);
	}



	template <typename T>
	template <typename U>
	void DataBase<T>::show_filter_records_of_table(const std::string& name_table, const U& type)
	{
		Table& table = __find_table(name_table);
		table.show_filter_by_field(type);
	}





	////////////////////////////////////////////////////////
	//                      TABLE
	////////////////////////////////////////////////////////

	

	template <typename T>
	DataBase<T>::Table::Table(const std::string& table_name, const std::string& path_to_file_with_table_names, const std::string& path_to_tables)
	{
		this->table_name = table_name;
		this->path_to_file_with_table_names = path_to_file_with_table_names;
		this->folder_width_tables = path_to_tables;

		if (file_functs::is_inclue(path_to_file_with_table_names, table_name))
		{
			this->__read_records_from_file(folder_width_tables + table_name + FILE_EXPANSION);
		}
		else
		{
			this->__write_name_to_file(path_to_file_with_table_names, table_name);
		}
		DataBase::amount_tables++;
	}



	template <typename T>
	DataBase<T>::Table::~Table() { DataBase::amount_tables--; }



	template<typename T>
	void DataBase<T>::Table::__write_name_to_file(const std::string& file_name, const std::string& name) const
	{
		std::ofstream out(path_to_file_with_table_names, std::ios::app);
		if (out.is_open())
		{
			out << ' ' + name;
			out.close();
		}
		else
		{
			system("CLS");
			std::cout << TABLE_ERROR << std::endl;
		}
	}



	template <typename T>
	void DataBase<T>::Table::__read_records_from_file(const std::string& name_file)
	{
		std::ifstream fin(name_file, std::ios::in);
		if (fin.is_open())
		{
			if (!file_functs::is_empty(name_file))
			{
				T record{};
				while (!fin.eof())
				{
					fin >> record;
					this->table_records.push_back(std::move(std::make_shared<T>(record)));
					this->amount_records++;
				}
			}
		}
		fin.close();
	}



	template <typename T>
	void DataBase<T>::Table::__write_record_to_file(const T& record) const
	{
		if (!std::filesystem::exists(folder_width_tables + this->table_name + FILE_EXPANSION))
		{
			DataBase::createFile(folder_width_tables + this->table_name + FILE_EXPANSION);
		}

		std::ofstream fout(folder_width_tables + this->table_name + FILE_EXPANSION, std::ios::app);

		if (fout.is_open())
		{
			if (this->amount_records != 0) { fout << '\n'; }
			fout << record;
			fout.close();
		}
		else
		{
			system("CLS");
			std::cout << TABLE_ERROR << std::endl;
		}
	}



	template <typename T>
	void DataBase<T>::Table::__delete_record_in_file(const std::string& name_file, const size_t& number_of_record)
	{
		std::ifstream file_in(name_file, std::ios::in);
		if (file_in)
		{
			T temp_container{};
			size_t index = 1;
#if CONTAINER == VECTOR
			std::vector<T> records;
#else
			my_array::Array<T> records;
#endif 

			while (!file_in.eof())
			{
				file_in >> temp_container;
				if (index++ != number_of_record)	records.push_back(temp_container);
			}
			file_in.close();

			std::ofstream file_out(name_file, std::ios::out);

			if (file_out)
			{
#if CONTAINER == VECTOR
				for (int i = 0; i < records.size(); ++i) { if (i != 0) { file_out << '\n'; } file_out << static_cast<T>(records[i]); }
#else
				for (int i = 0; i < records._size(); ++i) { if (i != 0) { file_out << '\n'; } file_out << static_cast<T>(records[i]); }
#endif 
				file_out.close();
			}
		}
	}


	
	template <typename T>
	const std::string& DataBase<T>::Table::get_name_table() const { return this->table_name; }



	template <typename T>
	const size_t& DataBase<T>::Table::get_amount_records() const { return this->amount_records; }



	template <typename T>
	bool DataBase<T>::Table::empty() const { return !(bool)this->amount_records; }



	template <typename T>
	void DataBase<T>::Table::rename_table(const std::string& new_name)
	{
		file_functs::replace_word(path_to_file_with_table_names, this->table_name, new_name);
		int res = std::rename((folder_width_tables + this->table_name + FILE_EXPANSION).c_str(),
			(folder_width_tables + new_name + FILE_EXPANSION).c_str());
		this->table_name = new_name;
	}



	template <typename T>
	void DataBase<T>::Table::add_record(const T& record)
	{
		this->table_records.push_back(std::make_shared<T>(record));
		this->__write_record_to_file(record);
		this->amount_records++;
	}



	template <typename T>
	bool DataBase<T>::Table::delete_record(const size_t number_of_table)
	{
		if (number_of_table > this->amount_records) { return false; }
#if CONTAINER == VECTOR
		auto it = this->table_records.begin();
		this->table_records.erase(it + number_of_table - 1);
#else
		this->table_records.erase(number_of_table - 1);
#endif
		this->__delete_record_in_file(folder_width_tables + this->table_name + FILE_EXPANSION, number_of_table);
		this->amount_records--;
		return true;
	}



	template <typename T>
	void my_db::DataBase<T>::Table::destroy()
	{
		file_functs::delete_word(path_to_file_with_table_names, this->table_name);
		remove((folder_width_tables + this->table_name + FILE_EXPANSION).c_str());
		this->amount_records = 0;
	}



	template <typename T>
	void DataBase<T>::Table::show_table()
	{
		T temp{};
		temp.show_titles();
		db_functs::show_div_line('_', WINDOW_WIDTH);	std::cout << std::endl;
#if CONTAINER == VECTOR
		for (int index = 0; index < table_records.size(); ++index)
#else
		for (int index = 0; index < table_records._size(); ++index)
#endif 
		{
			std::cout << '\t' << std::setw(WIDTH_COLUMN) << std::left << index + 1 << *table_records[index];
#if CONTAINER == VECTOR
			if (index != table_records.size() - 1)
#else
			if (index != table_records._size() - 1)
#endif
			{
				db_functs::show_div_line('-', WINDOW_WIDTH);
			}
		}
		db_functs::show_div_line('_', WINDOW_WIDTH);
		std::cout << "\n\tÊÎËÈ×ÅÑÒÂÎ ÇÀÏÈÑÅÉ Â ÁÀÇÅ ÄÀÍÍÛÕ:\t" << this->amount_records << std::endl;
		db_functs::show_div_line('_', WINDOW_WIDTH);
	}



	template <typename T>
	void DataBase<T>::Table::sort_records(const bool reverse) { db_functs::sort(this->table_records, reverse); }



	template <typename T>
	template <typename U>
	bool DataBase<T>::Table::show_finded_record(const U& value)
	{
#if CONTAINER == VECTOR
		for (int index = 0; index < table_records.size(); ++index)
#else
		for (int index = 0; index < table_records._size(); ++index)
#endif 
		{
			if (*table_records[index] == value)
			{
				std::cout << std::endl;
				db_functs::show_title("ÍÀÉÄÅÍÍÀß ÇÀÏÈÑÜ", WINDOW_WIDTH, '~');
				std::cout << "\n\t" << *table_records[index];
				db_functs::show_div_line('_', WINDOW_WIDTH);
				return true;
			}
		}
		return false;
	}



	template <typename T>
	template <typename U>
	void DataBase<T>::Table::show_filter_by_field(const U& value)
	{
		T temp{};
		temp.show_titles();
		db_functs::show_div_line('_', WINDOW_WIDTH);	std::cout << std::endl;
#if CONTAINER == VECTOR
		for (int index = 0; index < table_records.size(); ++index)
#else
		for (int index = 0; index < table_records._size(); ++index)
#endif 
		{
			if (table_records[index]->hasFiled(value))
			{
				std::cout << '\t' << std::setw(WIDTH_COLUMN) << std::left << index + 1 << *table_records[index];
#if CONTAINER == VECTOR
				if (index != table_records.size() - 1)
#else
				if (index != table_records._size() - 1)
#endif 
				{
					db_functs::show_div_line('-', WINDOW_WIDTH);
				}
			}
		}
		db_functs::show_div_line('_', WINDOW_WIDTH);
		std::cout << "\n\tÂÑÅÃÎ ÇÀÏÈÑÅÉ Â ÁÀÇÅ ÄÀÍÍÛÕ:\t" << this->amount_records << std::endl;
		db_functs::show_div_line('_', WINDOW_WIDTH);
	}
}


#endif // !DATA_BASE_HPP