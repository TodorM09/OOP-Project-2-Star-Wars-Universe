#pragma once
#include "Jedi.h"
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
public:
	Planet();
	Planet(const Planet& other);
	Planet& operator=(const Planet& other);
	~Planet();

	void serialize(std::ostream& out) const;
	void deserialize(std::istream& in);

	void createJedi(const char* jediName, Rank jediRank, size_t jediAge, const char* saberColour, double jediStrength);

	void setName(const char* m_name);
	const char* getName() const;

	void setSize(size_t m_size);
	size_t getSize() const;

	void setCapacity(size_t m_capacity);
	size_t getCapacity() const;
};

