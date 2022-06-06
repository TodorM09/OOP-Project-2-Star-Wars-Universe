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
