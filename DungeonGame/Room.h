#pragma once
#include <string>

using namespace std;

class Room
{
public:
	Room(int x, int y, Room* r);
	~Room();

	string getDescription();
	void setDescription(string desc);

	int getX() { return x; };
	int getY() { return y; };

	Room* opposite();

private:
	int x, y = 0;

	Room* parent = nullptr;

	Room* north = nullptr;
	Room* east = nullptr;
	Room* south = nullptr;
	Room* west = nullptr;

	string size;
	string state;
	string furniture;
	string light;

	string description = "x";
};

