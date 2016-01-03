#pragma once
<<<<<<< HEAD
#include "Room.h"
#include <string>
=======

class Room;

>>>>>>> 24210e13f45d3d761dd3ff33b641959b58c6ba85
class Hero
{
public:
	Hero(Room* start);
	~Hero();

<<<<<<< HEAD
	void setLocation(Room* room) { location = room; x = room->getX(); y = room->getY();  look(); };
	Room* getLocation() { return location; };
=======
	void setLocation(Room* currentRoom);
	Room* getLocation();
>>>>>>> 24210e13f45d3d761dd3ff33b641959b58c6ba85

	void look();
	void search();
	void move(string direction);
private:
	int x, y = 0;
	Room* currentRoom = nullptr; // current location of the hero

	int health = 50;

	Room* location = nullptr;
};

