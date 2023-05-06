#pragma once
#ifndef MEMORY_LEAKS_DEDUG
#define MEMORY_LEAKS_DEDUG

#include <iostream>
#include <Windows.h>

namespace MemoryDebug
{
	static const HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	static uint64_t leaks = 0;



	void* operator new(size_t size)
	{
		SetConsoleTextAttribute(h, 4);
		std::cout << "......Allocated " << size << " bytes" << std::endl;
		SetConsoleTextAttribute(h, 2);

		void* ptr = std::malloc(size);

		if (!ptr)
		{
			throw std::bad_alloc();
		}
		else
		{
			leaks += size;
			return ptr;
		}
	}



	void operator delete(void* ptr, size_t size) noexcept
	{
		SetConsoleTextAttribute(h, 3);
		std::cout << ".............................Free " << size << " bytes" << std::endl;
		SetConsoleTextAttribute(h, 2);

		leaks -= size;
		free(ptr);
	}



	inline static uint64_t getSizeMemoryLeaks()
	{
		return leaks;
	}
}

#endif // !MEMORY_LEAKS_DEDUG
