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
#include <vector>
#include <list>



namespace my_db
{
	template <typename T>
	class DataBase
	{
	public:

		DataBase(const std::string& path_to_file_with_table_names, const std::string& path_to_tables) noexcept;
		DataBase(const DataBase&) = delete;
		DataBase(DataBase&&) = delete;
		DataBase& operator=(const DataBase&) = delete;
		DataBase& operator=(DataBase&&) = delete;
		~DataBase() = default;



		static void set_executable_path(const std::string& _path_to_exe) noexcept;

		

		const std::string& get_ref_on_name_table(const std::string& name_table);
		const std::string& get_path_to_file_with_table_names() const noexcept;
		const size_t get_amount_records_of_table(const std::string table_name) const;

		void add_table(const std::string& name_table);
		void rename_table(const std::string& old_name_table, const std::string& new_name_table);
		void add_record_to_table(const std::string& name_table, const T& record, size_t index);
		bool delete_record_of_table(const std::string& name_table, const size_t number_of_record);
		void sort_records_of_table(const std::string& name_table, bool reverse = false);
		void delete_table(const std::string& name_table);
		void show_table(const std::string& name_table) const;
		bool table_is_empty(const std::string& name_table) const;
		void show_filter_records_of_table(const std::string& name_table, const std::string& profession) const;

		template <typename U>
		bool find_record_by_field(const std::string& name_table, const U& value) const;

		template <typename _Pred>
		void show_filter_records_of_table(const std::string& name_table, const _Pred& predicat) const;

	protected:

		class Table
		{
		private:

			size_t amount_records = 0;
			std::string path_to_file_with_table_names;
			std::string table_name;
			std::string folder_width_tables;
			std::list<std::shared_ptr<T>> table_records;

		private:

			void __write_name_to_file(const std::string& file_name, const std::string& name) const;
			void __read_records_from_file(const std::string& file_name);
			void __write_record_to_file(const T& record, bool in_back = true) const;
			void __delete_record_from_file(const std::string& name_file, const size_t number_of_record);

		public:

			Table() = default;
			Table(const Table&) = default;
			Table& operator=(const Table&) = default;
			Table(Table&&) = default;
			Table& operator=(Table&&) = default;
			Table(const std::string& table_name, const std::string& path_to_file_with_table_names, const std::string& path_to_tables) noexcept;
			~Table();



			const std::string& get_name_table() const noexcept;
			const size_t& get_amount_records() const noexcept;

			bool empty() const noexcept;
			void rename_table(const std::string& new_name);
			void add_record(const T& record, size_t index);
			bool delete_record(const size_t number_of_record);
			void destroy();
			void show_table() const noexcept;
			void sort_records(const bool reverse = false) noexcept;

			template <typename U>
			bool show_finded_record(const U& value) const noexcept;

			template <typename _Pred>
			void show_filter_records(const _Pred& predicat) const noexcept;
		};


	private:

		static void createFile(const std::string& _path);
		const Table& __find_table(const std::string& name_table) const;

	private:

		static size_t amount_tables;
		static std::string path_to_exe;

	private:

		std::list<Table> tables;
		std::string file_with_name_tabels;		
		std::string folder_width_tables;

	};





	template <typename T> size_t DataBase<T>::amount_tables = 0;
	template <typename T> std::string DataBase<T>::path_to_exe;



	////////////////////////////////////////////////////////
	//                      DATABASE
	////////////////////////////////////////////////////////

	

	template <typename T>
	void DataBase<T>::set_executable_path(const std::string& _path_to_exe) noexcept
	{
		path_to_exe = _path_to_exe.substr(0, _path_to_exe.find_last_of("\\/"));
	}

	

	template <typename T>
	DataBase<T>::DataBase(const std::string& path_to_file_with_table_names, const std::string& path_to_tables) noexcept
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
			throw std::runtime_error(("ERROR: Can't create file: " + _path).c_str());
		}
	}


	
	template <typename T>
	const DataBase<T>::template Table& DataBase<T>::__find_table(const std::string& name_table) const
	{
		for (auto it = tables.cbegin(); it != tables.cend(); ++it)
		{
			if (it->get_name_table() == name_table) 
			{
				return *it;
			}
		}
		throw std::runtime_error(("Table not found:" + name_table).c_str());
	}

	

	template <typename T>
	const std::string& DataBase<T>::get_ref_on_name_table(const std::string& name_table)
	{
		const Table& table = __find_table(name_table);
		return table.get_name_table();
	}



	template <typename T>
	const std::string& DataBase<T>::get_path_to_file_with_table_names() const noexcept
	{
		return file_with_name_tabels;
	}



	template <typename T>
	const size_t DataBase<T>::get_amount_records_of_table(const std::string table_name) const
	{
		const Table& table = __find_table(table_name);
		return table.get_amount_records();
	}



	template <typename T>
	void DataBase<T>::add_table(const std::string& name_table)
	{
		Table new_table(name_table, file_with_name_tabels, folder_width_tables);
		this->tables.push_back(std::move(new_table));
	}



	template <typename T>
	bool DataBase<T>::delete_record_of_table(const std::string& name_table, const size_t number_of_record)
	{
		Table& table = const_cast<Table&>(__find_table(name_table));
		return table.delete_record(number_of_record);
	}



	template <typename T>
	void DataBase<T>::sort_records_of_table(const std::string& name_table, bool reverse)
	{
		Table& table = const_cast<Table&>(__find_table(name_table));
		table.sort_records(reverse);
	}



	template <typename T>
	void DataBase<T>::rename_table(const std::string& old_name_table, const std::string& new_name_table)
	{
		Table& table = const_cast<Table&>(__find_table(old_name_table));
		table.rename_table(new_name_table);
	}



	template <typename T>
	void DataBase<T>::add_record_to_table(const std::string& name_table, const T& record, size_t index)
	{
		Table& table = const_cast<Table&>(__find_table(name_table));
		table.add_record(record, index);
	}



	template <typename T>
	void DataBase<T>::delete_table(const std::string& name_table)
	{
		auto it = tables.begin();
		for (; it != tables.end(); ++it)
		{
			if (it->get_name_table() == name_table)
			{
				it->destroy();
				break;
			}
		}
		tables.erase(it);
	}



	template <typename T>
	void DataBase<T>::show_table(const std::string& name_table) const
	{
		const Table& table = __find_table(name_table);
		table.show_table();
	}



	template <typename T>
	bool DataBase<T>::table_is_empty(const std::string& name_table) const
	{
		const Table& table = __find_table(name_table);
		return table.empty();
	}



	template <typename T>
	void DataBase<T>::show_filter_records_of_table(const std::string& name_table, const std::string& profession) const
	{
		const Table& table = __find_table(name_table);
		table.show_filter_records(profession);
	}



	template <typename T>
	template <typename U>
	bool DataBase<T>::find_record_by_field(const std::string& name_table, const U& person) const
	{
		const Table& table = __find_table(name_table);
		return table.show_finded_record(person);
	}



	template <typename T>
	template <typename _Pred>
	void DataBase<T>::show_filter_records_of_table(const std::string& name_table, const _Pred& predicat) const
	{
		const Table& table = __find_table(name_table);
		table.show_filter_records(predicat);
	}





	////////////////////////////////////////////////////////
	//                      TABLE
	////////////////////////////////////////////////////////

	



	template <typename T>
	DataBase<T>::Table::Table(const std::string& table_name, const std::string& path_to_file_with_table_names, const std::string& path_to_tables) noexcept
	{
		this->table_name = table_name;
		this->path_to_file_with_table_names = path_to_file_with_table_names;
		this->folder_width_tables = path_to_tables;

		try
		{
			if (file_functs::is_inclue(path_to_file_with_table_names, table_name))
			{
				__read_records_from_file(folder_width_tables + table_name + FILE_EXPANSION);
			}
			else
			{
				__write_name_to_file(path_to_file_with_table_names, table_name);
			}
		}
		catch (const std::exception& _ex)
		{
			std::cerr << _ex.what() << std::endl;
		}
		DataBase::amount_tables++;
	}



	template <typename T>
	DataBase<T>::Table::~Table()
	{
		DataBase::amount_tables--; 
	}



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
			throw std::runtime_error(("ERROR: Can't open file: " + file_name).c_str());
		}
	}



	template <typename T>
	void DataBase<T>::Table::__read_records_from_file(const std::string& name_file)
	{
		if (std::filesystem::exists(name_file))
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
						this->table_records.push_back(std::make_shared<T>(record));
						this->amount_records++;
					}
				}
			}
			else
			{
				throw std::exception(("ERROR: Can't open file: " + name_file).c_str());
			}
			fin.close();
		}
<<<<<<< Updated upstream
=======
		else
		{
			throw std::runtime_error(("ERROR: Can't open file: " + name_file).c_str());
		}
		fin.close();	
>>>>>>> Stashed changes
	}



	template <typename T>
	void DataBase<T>::Table::__write_record_to_file(const T& record, bool in_back) const
	{
		if (!std::filesystem::exists(folder_width_tables + this->table_name + FILE_EXPANSION))
		{
			DataBase::createFile(folder_width_tables + this->table_name + FILE_EXPANSION);
		}

		std::ofstream fout(folder_width_tables + this->table_name + FILE_EXPANSION, std::ios::out);

		if (fout.is_open())
		{
			if (amount_records == 0)
			{
				fout << record;
			}
			else
			{
				if (in_back)
				{
					fout << '\n';
					fout << record;
				}
				else
				{
					for (auto it = table_records.cbegin(); it != table_records.cend(); ++it)
					{
						fout << '\n';
						fout << *(*it);
					}
				}
			}
			fout.close();
		}
		else
		{
			throw std::runtime_error(("ERROR: Can't open file: " + this->table_name + FILE_EXPANSION).c_str());
		}
	}



	template <typename T>
	void DataBase<T>::Table::__delete_record_from_file(const std::string& name_file, const size_t number_of_record)
	{
		std::ifstream file_in(name_file, std::ios::in);
		if (file_in)
		{
			T temp_container{};
			size_t index = 1;
			std::list<T> records;

			while (!file_in.eof())
			{
				file_in >> temp_container;
				if (index++ != number_of_record)
				{
					records.push_back(temp_container);
				}
			}
			file_in.close();

			std::ofstream file_out(name_file, std::ios::out);

			if (file_out)
			{
				for (auto it = records.begin(); it != records.end(); ++it)
				{
					if (it != records.begin())
					{
						file_out << '\n';
					}
					file_out << static_cast<T>(*it);
				}
				file_out.close();
			}
		}
		else
		{
			throw std::runtime_error(("ERROR: Can't open file: " + name_file).c_str());
		}
	}


	
	template <typename T>
	const std::string& DataBase<T>::Table::get_name_table() const noexcept
	{
		return this->table_name; 
	}



	template <typename T>
	const size_t& DataBase<T>::Table::get_amount_records() const noexcept
	{
		return this->amount_records; 
	}



	template <typename T>
	bool DataBase<T>::Table::empty() const noexcept
	{
		return !static_cast<bool>(this->amount_records); 
	}



	template <typename T>
	void DataBase<T>::Table::rename_table(const std::string& new_name)
	{
		file_functs::replace_word(path_to_file_with_table_names, this->table_name, new_name);
		std::error_code _error;
		std::filesystem::rename((folder_width_tables + this->table_name + FILE_EXPANSION).c_str(),
								(folder_width_tables + new_name + FILE_EXPANSION).c_str(), _error);
		if (_error)
		{
			throw std::runtime_error(_error.message().c_str());
		}
		this->table_name = new_name;
	}



	template <typename T>
	void DataBase<T>::Table::add_record(const T& record, size_t index)
	{
		if (index >= table_records.size())
		{
			table_records.push_back(std::make_shared<T>(record));
			this->__write_record_to_file(record);
		}
		else
		{
			auto it = table_records.begin();
			for (size_t i = 0; i < index; ++i, ++it);
			this->table_records.insert(it, std::make_shared<T>(record));
			this->__write_record_to_file(record, false);
		}
		this->amount_records++;
	}



	template <typename T>
	bool DataBase<T>::Table::delete_record(const size_t number_of_table)
	{
		if (number_of_table > this->amount_records)
		{
			return false; 
		}
		auto it = table_records.cbegin();
		for (size_t current_number = 1; current_number < number_of_table; ++current_number, ++it);
		table_records.erase(it);
		__delete_record_from_file(folder_width_tables + this->table_name + FILE_EXPANSION, number_of_table);
		amount_records--;
		return true;
	}



	template <typename T>
	void my_db::DataBase<T>::Table::destroy()
	{
		file_functs::delete_word(path_to_file_with_table_names, this->table_name);
		std::error_code _error;
		std::filesystem::remove((folder_width_tables + this->table_name + FILE_EXPANSION).c_str(), _error);
		if (_error)
		{
			throw std::runtime_error(_error.message().c_str());
		}
		this->amount_records = 0;
	}



	template <typename T>
	void DataBase<T>::Table::show_table() const noexcept
	{
		T temp{};
		temp.show_titles();		std::cout << std::endl;
		db_functs::show_div_line('_', WINDOW_WIDTH);	std::cout << std::endl;
		size_t index = 0;
		for (auto it = table_records.cbegin(); it != table_records.cend(); ++index, ++it)
		{
			std::cout << '\t' << std::setw(WIDTH_COLUMN) << std::left << index + 1 << *(*it) << std::endl;
			if (index != table_records.size() - 1)
			{
				db_functs::show_div_line('-', WINDOW_WIDTH);
			}
		}
		db_functs::show_div_line('_', WINDOW_WIDTH);
		std::cout << "\n\tÊÎËÈ×ÅÑÒÂÎ ÇÀÏÈÑÅÉ Â ÁÀÇÅ ÄÀÍÍÛÕ:\t" << this->amount_records << std::endl;
		db_functs::show_div_line('_', WINDOW_WIDTH);
	}



	template <typename T>
	void DataBase<T>::Table::sort_records(const bool reverse) noexcept
	{
		if (reverse)
		{
			table_records.sort([](const std::shared_ptr<T>& _left, const std::shared_ptr<T>& _right)
				{
					return *_left > *_right;
				});
		}
		else
		{
			table_records.sort([](const std::shared_ptr<T>& _left, const std::shared_ptr<T>& _right)
				{
					return *_left < *_right;
				});
		}
	}



	template <typename T>
	template <typename U>
	bool DataBase<T>::Table::show_finded_record(const U& value) const noexcept
	{
		for (auto it = table_records.cbegin(); it != table_records.cend(); ++it)
		{
			if (*(*it) == value)
			{
				std::cout << std::endl;
				db_functs::show_title("ÍÀÉÄÅÍÍÀß ÇÀÏÈÑÜ", WINDOW_WIDTH, '~');
				std::cout << "\n\t" << *(*it) << std::endl;
				db_functs::show_div_line('_', WINDOW_WIDTH);
				return true;
			}
		}
		return false;
	}



	template <typename T>
	template <typename _Pred>
	void DataBase<T>::Table::show_filter_records(const _Pred& predicat) const noexcept
	{
		T temp{};
		temp.show_titles();	    std::cout << std::endl;
		db_functs::show_div_line('_', WINDOW_WIDTH);	std::cout << std::endl;
		size_t index = 0;
		for (auto it = table_records.cbegin(); it != table_records.cend(); ++index, ++it)
		{
			if (predicat(*(*it)))
			{
				std::cout << '\t' << std::setw(WIDTH_COLUMN) << std::left << index + 1 << *(*it) << std::endl;
				if (index != table_records.size() - 1)
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