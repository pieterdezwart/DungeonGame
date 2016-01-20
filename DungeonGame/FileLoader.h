#pragma once
#include <string>
#include <vector>
#include <fstream>

class Hero;
class Room;
class Item;
class Enemy;
class Trap;

class FileLoader
{
public:
	FileLoader();
	~FileLoader();

	void loadFile(std::string file);

	void parseHero();
	void parseRooms();
	void parseEnemies();
	void parseItems();
	void parseTraps();

private:
	std::vector<std::string> split(std::string str, char delim);


};

