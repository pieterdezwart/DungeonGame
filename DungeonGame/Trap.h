#pragma once
#include <string>

class Room;

class Trap
{
public:
	Trap(std::string n, int a) : name(n), attack(a) {};

	Trap(const Trap &obj);  // copy constructor

	~Trap();

	void setLocation(Room* room) { location = room; };
	Room* getLocation() { return location; };

	std::string getName() { return name; }
	int getAttack() { return attack; }

private:
	Room* location = nullptr;

	std::string name;
	int attack = 0;
};

