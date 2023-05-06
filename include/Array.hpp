#pragma once
#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>
#include <stdarg.h>



namespace my_array
{
	template <typename T>
	class Array
	{
	public:

		Array();
		Array(const size_t& size, const T& value);
		Array(const Array& outher);
		Array(Array&& outher);
		~Array();

		Array& operator = (const Array& outher);
		Array& operator = (Array&& outher);
		T& operator [] (const size_t& index);
		Array operator + (const Array& outher);

		size_t _size();
		size_t _capacity();
		
		void push_back(const T& value);
		void push_front(const T& value);
		void insert(const size_t& index, const T& value);

		T pop_back();
		T pop_front();
		T erase(const size_t& index);

		void clear();
		bool empty();
		bool is_include(const T& value);

		int find(const T& value);
		T& at(const size_t& index);
		Array extend(const Array& outher);
		void swap(const size_t& inxex1, const size_t& index2);

	private:

		T* data;
		size_t size;
		size_t capacity;

	};





	////////////////////////////////////////////////////////////////
	//              CONSTRUCTORS | DESTRUCTORS | ...
	////////////////////////////////////////////////////////////////



	template <typename T>
	Array<T>::Array()
	{
		capacity = size = 0;
		data = nullptr;
	}



	template <typename T>
	Array<T>::Array(const size_t& size, const T& value)
	{
		this->capacity = this->size = size;
		data = new T[size];
		for (int i = 0; i < size; i++) { data[i] = value; }
	}



	template <typename T>
	Array<T>::Array(const Array& outher)
	{
		this->data = new T[outher.capacity];
		this->size = outher.size;
		this->capacity = outher.capacity;

		for (int i = 0; i < size; i++) { if (i < size) this->data[i] = outher.data[i]; }
	}



	template <typename T>
	Array<T>::Array(Array&& outher)
	{
		this->data = outher.data;
		this->size = outher.size;
		this->capacity = outher.capacity;

		outher.data = nullptr;
		outher.size = outher.capacity = 0;
	}



	template <typename T>
	Array<T>::~Array() { if (data != nullptr) delete[] data; }



	////////////////////////////////////////////////////////////////
	//                        OPERATORS
	////////////////////////////////////////////////////////////////



	template <typename T>
	size_t Array<T>::_size() { return this->size; }



	template <typename T>
	size_t Array<T>::_capacity() { return this->capacity; }



	template <typename T>
	Array<T>& Array<T>::operator = (const Array<T>& outher)
	{
		if (this->data != outher.data)
		{
			this->data = new T[outher.capacity];
			this->size = outher.size;
			this->capacity = outher.capacity;

			for (int i = 0; i < size; i++) { this->data[i] = outher.data[i]; }
		}
		return *this;
	}



	template <typename T>
	Array<T>& Array<T>::operator = (Array<T>&& outher)
	{
		if (this->data != outher.data)
		{
			this->data = outher.data;
			this->size = outher.size;
			this->capacity = outher.capacity;

			outher.data = nullptr;
			outher.size = outher.capacity = 0;
		}
		return *this;
	}



	template <typename T>
	T& Array<T>::operator [] (const size_t& index)
	{
		return data[index];
	}



	template <typename T>
	Array<T> Array<T>::operator + (const Array<T>& outher)
	{
		Array<T> result;
		result.capacity = this->capacity + outher.capacity;
		result.size = this->size + outher.size;
		result.data = new T[result.capacity];
		int index = 0;

		for (; index < this->size; index++) { result.data[index] = this->data[index]; }
		for (int i = 0; i < outher.size; i++, index++) { result.data[index] = outher.data[i]; }

		return result;
	}



	////////////////////////////////////////////////////////////////
	//                         METHODS
	////////////////////////////////////////////////////////////////



	template <typename T>
	void Array<T>::push_back(const T& value)
	{
		if (data == nullptr)
		{
			size = 1;
			capacity = 2;
			data = new T[capacity];
			data[0] = value;
		}
		else if (size < capacity)
		{
			data[size++] = value;
		}
		else
		{
			capacity *= 2;
			T* new_data = new T[capacity];

			for (int i = 0; i < capacity / 2; i++) { new_data[i] = data[i]; }
			new_data[size++] = value;

			delete[] data;
			data = new_data;
		}
	}



	template <typename T>
	void Array<T>::push_front(const T& value)
	{
		if (data == nullptr)
		{
			size = 1;
			capacity = 2;
			data = new T[capacity];
			data[0] = value;
		}
		else if (size < capacity)
		{
			int index = size++;
			while (index > 0) { data[index] = data[--index]; }
			data[index] = value;
		}
		else
		{
			capacity *= 2;
			T* new_data = new T[capacity];

			new_data[0] = value;
			for (int i = 0; i < capacity / 2; i++) { new_data[i + 1] = data[i]; }

			delete[] data;
			data = new_data;
		}
	}



	template <typename T>
	void Array<T>::insert(const size_t& index, const T& value)
	{
		if (index < 1) { this->push_front(value); }
		else if (index >= size) { this->push_back(value); }
		else if (size < capacity)
		{
			for (int i = size++; i > index; i--) { data[i] = data[i - 1]; }
			data[index] = value;
		}
		else
		{
			capacity *= 2;
			T* new_data = new T[capacity];

			for (int i = 0; i < capacity / 2; )
			{
				if (i == index) { new_data[i] = value; continue; }
				new_data[i] = data[i++];
			}
			size++;
			delete[] data;
			data = new_data;
		}
	}



	template <typename T>
	T Array<T>::pop_back()
	{
		if (size == 0) throw std::exception("Array is empty");
		if (--size == 0 || size > capacity / 4) { return data[size]; }
		else
		{
			capacity /= 2;
			T* new_data = new T[capacity];

			for (int i = 0; i < size; i++) { new_data[i] = data[i]; }

			T value = data[size];

			delete[] data;
			data = new_data;
			return value;
		}
	}



	template <typename T>
	T Array<T>::pop_front()
	{
		if (size == 0) throw std::exception("Array is empty");
		if (--size == 0 || size > capacity / 4) { return data[size]; }
		else
		{
			capacity /= 2;
			T* new_data = new T[capacity];

			for (int i = 0; i < size; i++) { new_data[i] = data[i + 1]; }

			T value = data[0];

			delete[] data;
			data = new_data;
			return value;
		}
	}



	template <typename T>
	T Array<T>::erase(const size_t& index)
	{
		if (size == 0) { throw std::exception("Array is empty."); }
		if (index < 0 || index >= size) { throw std::exception("Index not found."); }
		else if (size - 1 >= capacity / 4)
		{
			T value = data[index];
			for (size_t i = index; i < size - 1; i++) { data[i] = data[i + 1]; }
			--size;
			return value;
		}
		else
		{
			capacity /= 2;
			T* new_data = new T[capacity];

			for (int i = 0; i < size--; )
			{
				if (i == index) { continue; }
				new_data[i] = data[i++];
			}

			T value = data[index];

			delete[] data;
			data = new_data;
			return value;
		}
	}



	template <typename T>
	void Array<T>::clear() { delete[] data; }



	template <typename T>
	bool Array<T>::empty() { return !(bool)size; }



	template <typename T>
	bool Array<T>::is_include(const T& value)
	{
		for (int i = 0; i < size; i++) { if (data[i] == value) return true; }
		return false;
	}



	template <typename T>
	int Array<T>::find(const T& value)
	{
		for (int i = 0; i < size; i++) { if (data[i] == value) return i; }
		throw std::exception("Element not found.");
	}



	template <typename T>
	T& Array<T>::at(const size_t& index)
	{
		if (index < 0 || index >= size) { throw std::exception("List index out of range."); }
		return data[index];
	}



	template <typename T>
	Array<T> Array<T>::extend(const Array& outher) { return *this + outher; }



	template <typename T>
	void Array<T>::swap(const size_t& index1, const size_t& index2)
	{
		T temp = data[index1];
		data[index1] = data[index2];
		data[index2] = temp;
	}
}

#endif // !ARRAY_HPP