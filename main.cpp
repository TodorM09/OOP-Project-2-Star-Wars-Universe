#include "Universe.h"

void execute(Universe& universe)
{
	std::cout << "Please enter a command!" << std::endl;
	char command[512];
	std::cin.get(command, 512,' ');
	if (strcmp(command, "open") == 0)
	{
		char filename[512];
		std::cin.getline(filename, 512);
		universe.getFromFile(filename);
		execute(universe);
	}

	if (strcmp(command, "saveas") == 0)
	{
		char filename[512];
		std::cin.getline(filename, 512);
		universe.writeInFile(filename);
		execute(universe);
	}

	if (strcmp(command, "addPlanet") == 0)
	{
		char planetName[512];
		std::cin.getline(planetName, 512);
		universe.addPlanet(planetName);
		execute(universe);
	}

	if (strcmp(command, "createJedi") == 0)
	{
		char planetName[512];
		char jediName[512];
		Rank jediRank;
		size_t jediAge;
		char sabercolour[512];
		double jediStrength;
		std::cin.get(planetName, 512, ' ');
		std::cin.get(jediName, 512, ' ');
		std::cin >> jediAge;
		std::cin.get(sabercolour, 512, ' ');
		std::cin >> jediStrength;
		jediRank = Rank::GRAND_MASTER;
		universe.createJedi(planetName, jediName, jediRank, jediAge, sabercolour, jediStrength);
		execute(universe);
	}

	if (strcmp(command, "removeJedi") == 0)
	{
		char planetName[512];
		char jediName[512];
		std::cin.get(planetName, 512, ' ');
		std::cin.get(jediName, 512, ' ');
		universe.removeJedi(planetName, jediName);
		execute(universe);
	}

	if (strcmp(command, "exit") == 0)
	{
		std::cout << "Exiting the program!" << std::endl;
		return;
	}
}

int main()
{
	std::cout << "type help for guidance and no help otherwise :)" << std::endl;
	char command[512];
	std::cin.getline(command, 512);
	Universe universe;
	if (strcmp(command, "help") == 0)
	{
		std::cout << "The following commands are supported:" << std::endl;
		std::cout << "open path  -> opens the file in that path" << std::endl;
		std::cout << "saveas path -> writes information in the file in that path" << std::endl;
		std::cout << "addPlanet planetName -> a planet is created" << std::endl;
		std::cout << "createJedi planetName jediName jediRank jediAge saberColour jediStrength ->creates a jedi with passed parameters" << std::endl;
		std::cout << "removeJedi planetName jediName -> removing the jedi with that name from the planet with the given name" << std::endl;
		std::cout << "exit -> terminates the program" << std::endl;
		execute(universe);
	}
	else
	{
		execute(universe);
	}
	execute(universe);
	return 0;
}