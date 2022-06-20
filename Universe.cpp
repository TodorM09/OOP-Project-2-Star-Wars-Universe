#include "Universe.h"

void Universe::copy(const Universe& other)
{
	size = other.size;
	capacity = other.capacity;
	int len = strlen(other.name);
	name = new char[len + 1];
	strcpy_s(name, len + 1, other.name);
	planets = new Planet[capacity];
	for (size_t i = 0; i < size; i++)
	{
		planets[i] = other.planets[i];
	}
}

void Universe::erase()
{
	delete[] name;
	delete[] planets;
	name = nullptr;
	planets = nullptr;
	size = 0;
	capacity = 1;
}

void Universe::resize()
{
	Planet* temp = new Planet[size];
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = planets[i];
	}
	delete[] planets;
	capacity *= 2;
	planets = new Planet[capacity];
	for (size_t i = 0; i < size; i++)
	{
		planets[i] = temp[i];
	}
	delete[] temp;
}

Universe::Universe()
{
	name = nullptr;
	planets = nullptr;
	size = 0;
	capacity = 1;
}

Universe::Universe(const Universe& other)
{
	copy(other);
}

Universe& Universe::operator=(const Universe& other)
{
	if (this != &other)
	{
		erase();
		copy(other);
	}
	return *this;
}

Universe::~Universe()
{
	erase();
}

void Universe::serialize(std::ostream& out) const
{
	size_t nameLen = strlen(name);
	out.write((char*)&nameLen, sizeof(nameLen));
	out.write(name, nameLen);

	out.write((char*)&size, sizeof(size));
	out.write((char*)&capacity, sizeof(capacity));

	for (size_t i = 0; i < size; i++)
	{
		planets[i].serialize(out);
	}
}

void Universe::deserialize(std::istream in)
{
	size_t nameLen = 0;
	in.read((char*)&nameLen, sizeof(nameLen));
	name = new char[nameLen];
	in.read(name, nameLen);

	in.read((char*)&size, sizeof(size));
	in.read((char*)&capacity, sizeof(capacity));

	for (size_t i = 0; i < size; i++)
	{
		planets[i].deserialize(in);
	}
}

void Universe::addPlanet(const char* m_name)
{
	if (size == capacity)
	{
		resize();
	}
	planets[size].setName(m_name);
}

void Universe::createJedi(const char* planetName, const char* jediName, Rank jediRank, size_t jediAge, const char* saberColour, double jediStrength)
{
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(planets[i].getName(), planetName) == 0)
		{
			planets[i].createJedi(jediName, jediRank, jediAge, saberColour, jediStrength);
		}
	}
}

void Universe::removeJedi(const char* jediName, const char* planetName)
{
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(planets[i].getName(), planetName) == 0)
		{
			planets[i].removeJedi(jediName);
		}
	}
}

void Universe::getStrongestJedi(const char* planetName)
{
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(planets[i].getName(), planetName) == 0)
		{
			planets[i].getStrongestJedi();
		}
	}
}

void Universe::getYoungestJedi(const char* planetName, const Rank& rank)
{
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(planets[i].getName(), planetName) == 0)
		{
			planets[i].getYoungestJedi(rank);
		}
	}
}

const char* Universe::getMostUsedSaberColour(const char* planetName, const Rank& rank)
{
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(planets[i].getName(), planetName) == 0)
		{
			return planets[i].getMostUsedSaberColour(rank);
		}
	}
}

const char* Universe::getMostUsedSaberColour(const char* planetName)
{
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(planets[i].getName(), planetName) == 0)
		{
			return planets[i].getMostUsedSaberColour();
		}
	}
}

void Universe::print(const char* planetName) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(planets[i].getName(), planetName) == 0)
		{
			planets[i].print();
		}
	}
}
