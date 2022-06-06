#include "Jedi.h"

void Jedi::copy(const char* m_name, Rank m_rank, size_t m_age, const char* colour, double m_power)
{
	strcpy_s(name, strlen(m_name + 1), m_name);
	rank = m_rank;
	age = m_age;
	strcpy_s(lightsaberColour, strlen(colour) + 1, colour);
	power = m_power;
}

void Jedi::erase()
{
	delete[] name;
	delete[] lightsaberColour;
	name = nullptr;
	lightsaberColour = nullptr;
}

Jedi::Jedi()
{
	name = nullptr;
	lightsaberColour = nullptr;
}

Jedi::Jedi(const char* m_name, Rank m_rank, size_t m_age, const char* colour, double m_power)
{
	copy(m_name, m_rank, m_age, colour, m_power);
}

Jedi::Jedi(const Jedi& other)
{
	copy(other.name, other.rank, other.age, other.lightsaberColour, other.power);
}

Jedi& Jedi::operator=(const Jedi& other)
{
	if (this != &other)
	{
		erase();
		copy(other.name, other.rank, other.age, other.lightsaberColour, other.power);
	}
	return *this;
}

Jedi::~Jedi()
{
	erase();
}

void Jedi::serialize(std::ostream& out) const
{
	size_t nameLen = strlen(name);
	out.write((char*)&nameLen, sizeof(nameLen));
	out.write(name, nameLen);

	out.write((char*)&rank, sizeof(rank));
	out.write((char*)&age, sizeof(age));

	size_t colourLen = strlen(lightsaberColour);
	out.write((char*)&colourLen, sizeof(colourLen));
	out.write(lightsaberColour, colourLen);

	out.write((char*)&power, sizeof(power));
}

void Jedi::deserialize(std::istream& in)
{
	size_t nameLen = 0;
	in.read((char*)&nameLen, sizeof(nameLen));
	char* tempName = new char[nameLen+1];
	in.read(tempName, nameLen);
	tempName[nameLen] = '\0';
	setName(tempName);
	delete[] tempName;

	Rank tempRank;
	in.read((char*)&tempRank, sizeof(tempRank));
	setRank(tempRank);

	size_t tempAge;
	in.read((char*)&tempAge, sizeof(tempAge));
	setAge(tempAge);

	size_t colourLen = 0;
	in.read((char*)&colourLen, sizeof(colourLen));
	char* tempColour = new char[colourLen + 1];
	in.read(tempColour, colourLen);
	tempColour[colourLen] = '\0';
	setColour(tempColour);
	delete[] tempColour;

	size_t tempPower;
	in.read((char*)&tempPower, sizeof(tempPower));
	setPower(tempPower);
}

void Jedi::setName(const char* m_name)
{
	size_t len = strlen(m_name);
	name = new char[len + 1];
	strcpy_s(name, len + 1, m_name);
}

void Jedi::setRank(const Rank& m_rank)
{
	rank = m_rank;
}

void Jedi::setAge(size_t m_age)
{
	age = m_age;
}

void Jedi::setColour(const char* m_colour)
{
	size_t len = strlen(m_colour);
	lightsaberColour = new char[len + 1];
	strcpy_s(lightsaberColour, len + 1, m_colour);
}

void Jedi::setPower(double m_power)
{
	power = m_power;
}

const char* Jedi::getName() const
{
	return name;
}

Rank Jedi::getRank() const
{
	return rank;
}

size_t Jedi::getAge() const
{
	return age;
}

const char* Jedi::getColour() const
{
	return lightsaberColour;
}

double Jedi::getPower() const
{
	return power;
}

void Jedi::promote(double multiplier)
{
	if (multiplier <= 0)
	{
		throw std::invalid_argument("Multiplier is not a positive double!");
	}
	power *= (1 + multiplier);
	switch (rank)
	{
	case Rank::YOUNGLING: rank = Rank::INITIATE;
		break;
	case Rank::INITIATE: rank = Rank::PADAWAN;
		break;
	case Rank::PADAWAN: rank = Rank::KNIGHTASPIRANT;
		break;
	case Rank::KNIGHTASPIRANT: rank = Rank::KNIGHT;
		break;
	case Rank::KNIGHT: rank = Rank::MASTER;
		break;
	case Rank::MASTER: rank = Rank::BATTLE_MASTER;
		break;
	case Rank::BATTLE_MASTER: rank = Rank::GRAND_MASTER;
		break;
	case Rank::GRAND_MASTER:
		break;
	}
}

void Jedi::demote(double multiplier)
{
	if (multiplier <= 0)
	{
		throw std::invalid_argument("Multiplier is not a positive double!");
	}
	power *= (1 - multiplier);
	switch (rank)
	{
	case Rank::YOUNGLING:
		break;
	case Rank::INITIATE: rank = Rank::YOUNGLING;
		break;
	case Rank::PADAWAN: rank = Rank::INITIATE;
		break;
	case Rank::KNIGHTASPIRANT: rank = Rank::PADAWAN;
		break;
	case Rank::KNIGHT: rank = Rank::KNIGHTASPIRANT;
		break;
	case Rank::MASTER: rank = Rank::KNIGHT;
		break;
	case Rank::BATTLE_MASTER: rank = Rank::MASTER;
		break;
	case Rank::GRAND_MASTER: rank = Rank::BATTLE_MASTER;
		break;
	}
}

bool Jedi::operator<(const Jedi& other)
{
	if (rank > other.getRank())
	{
		return false;
	}
	else if (rank < other.getRank())
	{
		return true;
	}
	else
	{
		if (strcmp(name, other.name) < 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

void Jedi::print() const
{
	std::cout << "Name:" << name << std::endl;
	std::cout << "Rank:";
	switch (rank)
	{
	case Rank::YOUNGLING: std::cout << "YOUNGLING" << std::endl;
		break;
	case Rank::INITIATE: std::cout << "INITIATE" << std::endl;
		break;
	case Rank::PADAWAN: std::cout << "PADAWAN" << std::endl;
		break;
	case Rank::KNIGHTASPIRANT: std::cout << "KNIGHTASPIRANT" << std::endl;
		break;
	case Rank::KNIGHT: std::cout << "KNIGHT" << std::endl;
		break;
	case Rank::MASTER: std::cout << "MASTER" << std::endl;
		break;
	case Rank::BATTLE_MASTER: std::cout << "BATTLE_MASTER" << std::endl;
		break;
	case Rank::GRAND_MASTER: std::cout << "GRAND_MASTER" << std::endl;
		break;
	}
	std::cout << "Age:" << age << std::endl;
	std::cout << "Lightsaber colour:" << lightsaberColour << std::endl;
	std::cout << "Power value:" << power << std::endl;
}
