#pragma once
#include "Room.h"
#include <string>
#include "Item.h"

class Hero
{
public:
	//Hero(Room* start);
	Hero(std::string n) : name(n) {};
	Hero(std::string n, int l, int h, int x, int a, int d, int p) : name(n), level(l), health(h), experience(x), attack(a), defense(d), perception(p) {};
	~Hero();

	void setLocation(Room* room);
	Room* getLocation() { return location; };

	void look();
	void search();
	bool move(string direction);
	
	std::string getName() { return name; }
	void addPerception(int xp) { perception += xp; };
	int getPerception() { return perception; }
	void setLevel(int l) { level = l; }
	int getLevel() { return level; }
	int getExp() { return experience; }
	void addExp(int x) { experience += x; }
	int getHealth() { return health; }
	int getMaxHealth() { return maxHealth; }
	void setHealth(int h) { health = h; }
	int getAttack() { return (weapon == nullptr) ? attack : attack + weapon->getAttack(); }
	void setAttack(int a) { attack = a; }
	int getDefense() { return (shield == nullptr) ? defense : defense + shield->getDefense(); }
	void setDefense(int d) { defense = d; }

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
	std::string name = "default";
	int perception = 1;
	int health = 50;
	int maxHealth = 50;
	int attack = 1;
	int defense = 1;
	int level = 1;
	int experience = 0;

	void setWeapon(Item* weap) { if (weap->getAttack() > 0) weapon = weap; };
	void setShield(Item* shld) { if (shld->getDefense() > 0) shield = shld; };
	void usePotion(Item* i);
	vector<Item*> inventory;
	Item* weapon = nullptr;
	Item* shield = nullptr;
};

