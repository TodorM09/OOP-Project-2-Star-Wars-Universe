#include "Planet.h"

void Planet::copy(const Planet& other)
{
	setName(other.getName());
	size = other.size;
	capacity = other.capacity;
	jedi = new Jedi[size];
	for (size_t i = 0; i < size; i++)
	{
		jedi[i] = other.jedi[i];
	}
}

void Planet::erase()
{
	delete[] jedi;
	jedi = nullptr;
	size = 0;
	capacity = 1;
}

void Planet::resize()
{
	Jedi* temp = new Jedi[size];
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = jedi[i];
	}
	size_t tempSize = size;
	size_t tempCapacity = capacity;
	erase();
	size = tempSize;
	capacity = tempCapacity * 2;
	jedi = new Jedi[capacity];
	for (size_t i = 0; i < size; i++)
	{
		jedi[i] = temp[i];
	}
	delete[] temp;
	
}

void Planet::sortByRank()
{
	for (size_t i = 0; i < size-1; i++)
	{
		for (size_t j = i+1; j < size; j++)
		{
			if (jedi[j] < jedi[i])
			{
				jedi[i].swap(jedi[j]);
			}
		}
	}
}

void Planet::sortByNames()
{
	for (size_t i = 0; i < size-1; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			int temp = strcmp(jedi[i].getName(), jedi[j].getName());
			if (temp > 0)
			{
				jedi[i].swap(jedi[j]);
			}
		}
	}
}

Planet::Planet()
{
	name = nullptr;
	jedi = nullptr;
	size = 0;
	capacity = 1;
}

Planet::Planet(const Planet& other)
{
	copy(other);
}

Planet& Planet::operator=(const Planet& other)
{
	if (this != &other)
	{
		erase();
		copy(other);
	}
	return *this;
}

Planet::~Planet()
{
	erase();
}

void Planet::serialize(std::ostream& out) const
{
	size_t nameLen = strlen(name);
	out.write((char*)&nameLen, sizeof(nameLen));
	out.write(name, nameLen);

	out.write((char*)&size, sizeof(size));
	out.write((char*)&capacity, sizeof(capacity));

	for (size_t i = 0; i < size; i++)
	{
		jedi[i].serialize(out);
	}
}

void Planet::deserialize(std::istream& in)
{
	size_t nameLen = 0;
	in.read((char*)&nameLen, sizeof(nameLen));
	char* tempName = new char[nameLen + 1];
	in.read(tempName, nameLen);
	tempName[nameLen] = '\0';
	setName(tempName);
	delete[] tempName;

	size_t tempSize;
	in.read((char*)&tempSize, sizeof(tempSize));
	setSize(tempSize);

	size_t tempCapacity;
	in.read((char*)&tempCapacity, sizeof(tempCapacity));
	setCapacity(tempCapacity);

	for (size_t i = 0; i < size; i++)
	{
		jedi[i].deserialize(in);
	}
}

void Planet::createJedi(const char* jediName, Rank jediRank, size_t jediAge, const char* saberColour, double jediStrength)
{
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(jedi[i].getName(), jediName) == 0)
		{
			std::cout << "Such jedi already exists!" << std::endl;
			return;
		}
	}
	if (size == capacity)
	{
		resize();
	}
	Jedi temp(jediName, jediRank, jediAge, saberColour, jediStrength);
	jedi[size] = temp;
}

void Planet::removeJedi(const char* jediName)
{
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(jedi[i].getName(), jediName) == 0)
		{
			jedi[i].~Jedi();
			for (size_t j = i; j < size-1; j++)
			{
				jedi[j] = jedi[j + 1];
			}
			jedi[size - 1].~Jedi();
			size--;
			std::cout << "Jedi removed successfully!" << std::endl;
			return;
		}
	}
	std::cout << "Such jedi does not inhabit this planet!" << std::endl;
}

void Planet::promoteJedi(const char* jediName, double multiplier)
{
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(jedi[i].getName(), jediName) == 0)
		{
			jedi[i].promote(multiplier);
		}
	}
}

void Planet::demoteJedi(const char* jediName, double multiplier)
{
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(jedi[i].getName(), jediName) == 0)
		{
			jedi[i].demote(multiplier);
		}
	}
}

void Planet::getStrongestJedi() const //void because the task asks for print
{
	double maxPower = 0;
	size_t index;
	for (size_t i = 0; i < size; i++)
	{
		if (maxPower < jedi[i].getPower())
		{
			index = i;
		}
	}
	std::cout << "Most powerful jedi is:" << std::endl;
	jedi[index].print();
}

void Planet::getYoungestJedi(const Rank& rank) //void because the task asks for print
{
	sortByRank();
	size_t index;
	for (size_t i = 0; i < size; i++)
	{
		if (jedi[i].getRank() == rank)
		{
			index = i;
			size_t minAge = jedi[i].getAge();
			for (size_t j = i+1; j < size; j++)
			{
				if (jedi[j].getRank() == rank)
				{
					if (jedi[j].getAge() < minAge)
					{
						minAge = jedi[j].getAge();
						index = j;
					}
				}
				else
				{
					break;
				}
			}
			std::cout << "Youngest jedi is:" << std::endl;
			jedi[index].print();
		}
		break;
	}
}

const char* Planet::getMostUsedSaberColour(const Rank& rank) const
{
	Pair** histogram = new Pair * [size];
	for (size_t i = 0; i < size; i++)
	{
		if (jedi[i].getRank() == rank)
		{
			int len = strlen(jedi[i].getColour());
			strcpy_s(histogram[i]->first, len + 1, jedi[i].getColour());
			histogram[i]->second = 1;
		}
	}

	for (size_t i = 0; i < size-1; i++)
	{
		for (size_t j = i + 1; j < size; j++)
		{
			if (histogram[i]->second != 0)
			{
				if (strcmp(histogram[i]->first, histogram[j]->first) == 0)
				{
					histogram[i]->second++;
					histogram[j]->second--;
				}
			}
		}
	}

	int max = 0;
	int index;
	for (size_t i = 0; i < size; i++)
	{
		if (histogram[i]->second > max)
		{
			max = histogram[i]->second;
			index = i;
		}
	}
	if (max == 0)
	{
		std::cout << "There are no jedi on the planet yet!" << std::endl;
		return nullptr;
	}

	int len = strlen(histogram[index]->first);
	char* temp = new char[len + 1];
	strcpy_s(temp, len + 1, histogram[index]->first);

	for (size_t i = 0; i < size; i++)
	{
		delete[] histogram[i];
	}
	delete[] histogram;
	return temp;
}

const char* Planet::getMostUsedSaberColour() const
{
	
	return getMostUsedSaberColour(Rank::GRAND_MASTER);
}

void Planet::print()
{
	std::cout << getName() << std::endl;
	sortByRank();
	for (size_t i = 0; i < size; i++)
	{
		jedi[i].print();
	}
}

void Planet::operator+(const Planet& other)
{
	std::cout << "All jedi in both planets:" << std::endl;
	Planet temp;
	temp.setCapacity((size + other.getSize()));//no need for extra capacity because there will be no new jedi added.
	temp.setSize((size + other.getSize()));
	temp.jedi = new Jedi[capacity];
	for (size_t i = 0; i < size; i++)
	{
		temp.jedi[i] = jedi[i];
	}
	for (size_t i = size; i < temp.getSize(); i++)
	{
		temp.jedi[i] = other.jedi[i];
	}
	temp.sortByNames();
	for (size_t i = 0; i < temp.getSize(); i++)
	{
		temp.getJedi()[i].print();
	}
}

void Planet::setName(const char* m_name)
{
	size_t len = strlen(m_name);
	name = new char[len + 1];
	strcpy_s(name, len + 1, m_name);
}

const char* Planet::getName() const
{
	return name;
}

void Planet::setSize(size_t m_size)
{
	size = m_size;
}

size_t Planet::getSize() const
{
	return size;
}

void Planet::setCapacity(size_t m_capacity)
{
	capacity = m_capacity;
}

size_t Planet::getCapacity() const
{
	return capacity;
}

const Jedi* Planet::getJedi() const
{
	return jedi;
}
