#pragma once
#include "Room.h"
#include <string>

class Hero
{
public:
	Hero(Room* start);
	~Hero();

	void setLocation(Room* room);
	Room* getLocation() { return location; };

	void look();
	void search();
	bool move(string direction);
	
	void addPerception(int xp) { perception += xp; };
	int getHealth() { return health; }
	int getMaxHealth() { return maxHealth; }
	void setHealth(int h) { health = h; }
	int getAttack() { return attack; }
	void setAttack(int a) { attack = a; }
	void printStats();
private:
	int x, y = 0;
	Room* currentRoom = nullptr; // current location of the hero

	Room* location = nullptr;

	//stats
	int perception = 0;
	int health = 5;
	int maxHealth = 50;
	int attack = 1;
	int level = 1;

};

