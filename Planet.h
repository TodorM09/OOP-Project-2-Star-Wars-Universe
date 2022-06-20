#pragma once
#include "Jedi.h"
#include "Pair.h"
class Planet
{
private:
	char* name;
	Jedi* jedi;
	size_t size;
	size_t capacity;
	void copy(const Planet& other);
	void erase();
	void resize();
	void sortByRank();
	void sortByNames();
public:
	Planet();
	Planet(const Planet& other);
	Planet& operator=(const Planet& other);
	~Planet();

	void serialize(std::ostream& out) const;
	void deserialize(std::istream& in);

	void createJedi(const char* jediName, Rank jediRank, size_t jediAge, const char* saberColour, double jediStrength);
	void removeJedi(const char* jediName);
	void promoteJedi(const char* jediName, double multiplier);
	void demoteJedi(const char* jediName, double multiplier);
	void getStrongestJedi() const;
	void getYoungestJedi(const Rank& rank);
	const char* getMostUsedSaberColour(const Rank& rank) const;
	const char* getMostUsedSaberColour() const;
	void print();
	void operator+(const Planet& other);

	void setName(const char* m_name);
	const char* getName() const;

	void setSize(size_t m_size);
	size_t getSize() const;

	void setCapacity(size_t m_capacity);
	size_t getCapacity() const;

	const Jedi* getJedi() const;
};

