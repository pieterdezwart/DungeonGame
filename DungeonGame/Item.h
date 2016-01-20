#pragma once
#include <string>

class Room;

class Item
{
public:
	Item(int i, std::string n, int a, int d, int h, int p) : id(i), name(n), attack(a), defense(d), health(h), perception(p) {};

	//Item(const Item &obj);  // copy constructor

	~Item();

	void setLocation(Room* room) { location = room; };
	Room* getLocation() { return location; };

	int getID() { return id; }
	std::string getName() { return name; }
	int getAttack() { return attack; }
	int getDefense() { return defense; }
	int getHealth() { return health; };
	int getPerception() { return perception; }
private:
	Room* location = nullptr;

	int id = 0; // unique identifier
	std::string name;
	int attack = 0;
	int defense = 0;
	int health = 0;
	int perception = 0;
};

