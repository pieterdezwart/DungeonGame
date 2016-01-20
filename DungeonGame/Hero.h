#pragma once
#include "Room.h"
#include <string>
#include "Item.h"

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
	int getAttack() { return (weapon == nullptr) ? attack : attack + weapon->getAttack(); }
	void setAttack(int a) { attack = a; }
	void printStats();
	//inventory
	void addToInventory(Item* i) { inventory.push_back(i); i->setLocation(nullptr); };
	vector<Item*> getInventory() { return inventory; };
	void useItem(Item* i);
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
	int defense = 0;

	void setWeapon(Item* weap) { if (weap->getAttack() > 0) weapon = weap; };
	void setShield(Item* shld) { if (shld->getDefense() > 0) shield = shld; };
	void usePotion(Item* i);
	vector<Item*> inventory;
	Item* weapon = nullptr;
	Item* shield = nullptr;
};

