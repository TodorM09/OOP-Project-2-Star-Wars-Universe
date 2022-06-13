#pragma once
#include <iostream>
#include <cstring>
#include <stdexcept>
enum class Rank
{
	YOUNGLING=1, INITIATE, PADAWAN, KNIGHTASPIRANT, KNIGHT, MASTER, BATTLE_MASTER, GRAND_MASTER
};
class Jedi
{
private:
	char* name;
	Rank rank;
	size_t age;
	char* lightsaberColour;
	double power;
	void copy(const char* m_name, Rank m_rank, size_t m_age, const char* colour, double m_power);
	void erase();
public:
	Jedi();
	Jedi(const char* m_name, Rank m_rank, size_t m_age, const char* colour, double m_power);
	Jedi(const Jedi& other);
	Jedi& operator=(const Jedi& other);
	~Jedi();

	void serialize(std::ostream& out) const;
	void deserialize(std::istream& in);

	void setName(const char* m_name);
	void setRank(const Rank& m_rank);
	void setAge(size_t m_age);
	void setColour(const char* m_colour);
	void setPower(double m_power);

	const char* getName() const;
	Rank getRank() const;
	size_t getAge() const;
	const char* getColour() const;
	double getPower() const;

	void promote(double multiplier);
	void demote(double multiplier);

	bool operator<(const Jedi& other);
	void swap(Jedi& other);
	void print() const;
};

