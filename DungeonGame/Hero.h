#pragma once
#include "Room.h"
#include <string>

class Hero
{
public:
	Hero(Room* start);
	~Hero();

	void setLocation(Room* room) { location = room; x = room->getX(); y = room->getY(); room->setExplored(true); look(); };
	Room* getLocation() { return location; };

	void look();
	void search();
	bool move(string direction);
private:
	int x, y = 0;
	Room* currentRoom = nullptr; // current location of the hero

	int health = 50;

	Room* location = nullptr;
};

