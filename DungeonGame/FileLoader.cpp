#include <sstream>
#include <iostream>

#include "FileLoader.h"
#include "Game.h"

FileLoader::FileLoader()
{
	parseRooms();
	parseEnemies();
	parseItems();
	parseTraps();
	parseHero();
}


FileLoader::~FileLoader()
{
}


void FileLoader::parseHero()
{
	std::ifstream input;

	input.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		input.open("Resources/hero.txt");

		std::string line;

		while (!input.eof())
		{
			getline(input, line, '\n');

			std::vector<std::string> tokens = split(line, ',');

			if (tokens.at(0) == "properties")
			{
				Game::getInstance().setHero(new Hero(tokens.at(1), std::stoi(tokens.at(2)), std::stoi(tokens.at(3)), std::stoi(tokens.at(4)), std::stoi(tokens.at(5)), std::stoi(tokens.at(6)), std::stoi(tokens.at(7))));
			}
			if (tokens.at(0) == "items")
			{
				for (std::string token : tokens)
				{
					for (Item* item : Game::getInstance().getItems())
					{
						if (token != tokens.at(0) && std::stoi(token) == item->getID()) Game::getInstance().getHero()->addToInventory(item);
					}
				}
			}

		}
	}
	catch (std::ifstream::failure e) {
		std::cout << "Error opening/reading file: " << e.what() << std::endl;
	}
	if (input.is_open())
		input.close();

}

void FileLoader::parseRooms()
{
	std::ifstream input;

	input.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		input.open("Resources/room.txt");

		std::string line;

		while (!input.eof())
		{
			getline(input, line, '\n');

			std::vector<std::string> tokens = split(line, ',');

			if (tokens.at(0) == "1")
			{
				for (std::string token : tokens)
				{
					if (token != tokens.at(0)) Game::getInstance().addRoomSize(token);
				}
			}
			if (tokens.at(0) == "2")
			{
				for (std::string token : tokens)
				{
					if (token != tokens.at(0)) Game::getInstance().addRoomState(token);
				}
			}
			if (tokens.at(0) == "3")
			{
				for (std::string token : tokens)
				{
					if (token != tokens.at(0)) Game::getInstance().addRoomProperties(token);
				}
			}
			if (tokens.at(0) == "4")
			{
				for (std::string token : tokens)
				{
					if(token != tokens.at(0)) Game::getInstance().addRoomLight(token);
				}
			}
			if (tokens.at(0) == "5")
			{
				for (std::string token : tokens)
				{
					if (token != tokens.at(0)) Game::getInstance().addRoomAtmosphere(token);
				}
			}
			if (tokens.at(0) == "6")
			{
				for (std::string token : tokens)
				{
					if (token != tokens.at(0)) Game::getInstance().addRoomWall(token);
				}
			}

		}
	}
	catch (std::ifstream::failure e) {
		std::cout << "Error opening/reading file: " << e.what() << std::endl;
	}
	if (input.is_open())
		input.close();
}

void FileLoader::parseEnemies()
{
	std::ifstream input;

	input.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		input.open("Resources/enemy.txt");

		std::string line;

		while (!input.eof())
		{
			getline(input, line, '\n');

			vector<string> enemyProperties = split(line, ',');

			if(std::stoi(enemyProperties.at(5)) == 0)
				Game::getInstance().addEnemy(new Enemy(enemyProperties.at(0), std::stoi(enemyProperties.at(1)), std::stoi(enemyProperties.at(2)), std::stoi(enemyProperties.at(3)), std::stoi(enemyProperties.at(4)), std::stoi(enemyProperties.at(5))));
			else 
				Game::getInstance().addBoss(new Enemy(enemyProperties.at(0), std::stoi(enemyProperties.at(1)), std::stoi(enemyProperties.at(2)), std::stoi(enemyProperties.at(3)), std::stoi(enemyProperties.at(4)), std::stoi(enemyProperties.at(5))));
		}
	}
	catch (std::ifstream::failure e) {
		std::cout << "Error opening/reading file: " << e.what() << std::endl;
	}
	if (input.is_open())
		input.close();
}

void FileLoader::parseItems()
{
	std::ifstream input;

	input.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		input.open("Resources/item.txt");

		std::string line;

		while (!input.eof())
		{
			getline(input, line, '\n');

			vector<string> trapProperties = split(line, ',');

			Game::getInstance().addItem(new Item(std::stoi(trapProperties.at(0)), trapProperties.at(1), std::stoi(trapProperties.at(2)), std::stoi(trapProperties.at(3)), std::stoi(trapProperties.at(4)), std::stoi(trapProperties.at(5))));

		}
	}
	catch (std::ifstream::failure e) {
		std::cout << "Error opening/reading file: " << e.what() << std::endl;
	}
	if (input.is_open())
		input.close();

}

void FileLoader::parseTraps()
{
	std::ifstream input;

	input.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		input.open("Resources/trap.txt");

		std::string line;

		while (!input.eof())
		{
			getline(input, line, '\n');

			vector<string> trapProperties = split(line, ',');

			Game::getInstance().addTrap(new Trap(trapProperties.at(0), std::stoi(trapProperties.at(1))));

		}
	}
	catch (std::ifstream::failure e) {
		std::cout << "Error opening/reading file: " << e.what() << std::endl;
	}
	if (input.is_open())
		input.close();

}

void FileLoader::saveHero()
{
	std::ofstream output;

	output.exceptions(std::ofstream::failbit | std::ofstream::badbit);

	try
	{
		output.open("Resources/hero.txt");

		Hero* tempHero = Game::getInstance().getHero();

		output << "properties," << tempHero->getName() << "," << tempHero->getLevel() << "," << tempHero->getHealth() << "," << tempHero->getExp() << "," << tempHero->getAttack() << "," << tempHero->getDefense() << "," << tempHero->getPerception() << "\n";
		output << "items,";

		for (Item* item : tempHero->getInventory())
		{
			output << item->getID();
			if (tempHero->getInventory().back() != item) ",";
		}
	}
	catch (std::ofstream::failure e) {
		std::cout << "Error writing/opening file: " << e.what() << std::endl;
	}
	if (output.is_open())
		output.close();
}

std::vector<std::string> FileLoader::split(std::string str, char delim)
{
	std::vector<std::string> tokens;
	std::stringstream ss(str);
	std::string item;

	while (getline(ss, item, delim)) {
		tokens.push_back(item);
	}

	return tokens;
}
