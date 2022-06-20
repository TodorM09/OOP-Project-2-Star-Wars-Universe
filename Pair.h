#pragma once
#include <cstring>
struct Pair
{
	char* first;
	int second;

	Pair()
	{
		first = nullptr;
		second = 0;
	}
	Pair(const char* m_first, int m_second)
	{
		int len = strlen(m_first);
		strcpy_s(first, len + 1, m_first);
		second = m_second;
	}
	Pair(const Pair& other)
	{
		int len = strlen(other.first);
		strcpy_s(first, len + 1, other.first);
		second = other.second;
	}
	Pair operator=(const Pair& other)
	{
		if (this != &other)
		{
			delete[] first;
			int len = strlen(other.first);
			strcpy_s(first, len + 1, other.first);
			second = other.second;
		}
		return *this;
	}
	~Pair()
	{
		delete[] first;
	}
};