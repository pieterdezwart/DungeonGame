#pragma once

class Room;

class Hero
{
public:
	Hero();
	~Hero();

	void setLocation(Room* currentRoom);
	Room* getLocation();

private:
	int x, y = 0;
	Room* currentRoom = nullptr; // current location of the hero

	int health = 50;
};

