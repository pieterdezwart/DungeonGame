#pragma once
#include <string>

class Room;

class Item
{
public:
	Item(std::string n, int a, int d, int h) : name(n), attack(a), defense(d), health(h) {};

	//Item(const Item &obj);  // copy constructor

	~Item();

	void setLocation(Room* room) { location = room; };
	Room* getLocation() { return location; };

	std::string getName() { return name; }
	int getAttack() { return attack; }
	int getDefense() { return defense; }
	int getHealth() { return health; };
private:
	Room* location = nullptr;

	std::string name;
	int attack = 0;
	int defense = 0;
	int health = 0;
};

