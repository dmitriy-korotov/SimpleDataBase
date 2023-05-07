#pragma once
#ifndef MEMORY_LEAKS_DEDUG
#define MEMORY_LEAKS_DEDUG

#include <iostream>
#include <Windows.h>



static const HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
static uint64_t leaks = 0;



inline static uint64_t getSizeMemoryLeaks()
{
	return leaks;
}



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

	std::cout << "\t\t\t\t\t\t\tMemory leaks: " << getSizeMemoryLeaks() << std::endl;
}

#endif // !MEMORY_LEAKS_DEDUG
