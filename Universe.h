#pragma once
#include "Planet.h"
#include <fstream>
class Universe
{
private:
	char* name;
	Planet* planets;
	int size;
	int capacity;
	void copy(const Universe& other);
	void erase();
	void resize();
public:
	Universe();
	Universe(const Universe& other);
	Universe& operator=(const Universe& other);
	~Universe();

	void serialize(std::ostream& out) const;
	void deserialize(std::istream& in);
	void writeInFile(const char* fileName);
	void getFromFile(const char* fileName);

	void addPlanet(const char* m_name);
	void createJedi(const char* planetName, const char* jediName, Rank jediRank,
					size_t jediAge, const char* saberColour, double jediStrength);
	void removeJedi(const char* jediName, const char* planetName);

	void getStrongestJedi(const char* planetName);//task demands print ->void
	void getYoungestJedi(const char* planetName, const Rank& rank);//same reason

	const char* getMostUsedSaberColour(const char* planetName, const Rank& rank);
	const char* getMostUsedSaberColour(const char* planetName);

	void print(const char* planetName) const;
};

