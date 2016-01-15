#pragma once
#include "Room.h"
#include <string>

class Hero
{
public:
	Hero(Room* start);
	~Hero();

	void setLocation(Room* room) { location = room; x = room->getX(); y = room->getY(); room->setExplored(true); };
	Room* getLocation() { return location; };

	void look();
	void search();
	bool move(string direction);
	
	void addPerception(int xp) { perception += xp; };
	int getHealth() { return health; }
	int getMaxHealth() { return maxHealth; }

private:
	int x, y = 0;
	Room* currentRoom = nullptr; // current location of the hero

	Room* location = nullptr;

	//stats
	int perception = 0;
	int health = 50;
	int maxHealth = 50;

};

