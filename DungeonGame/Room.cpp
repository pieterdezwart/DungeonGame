#include "Room.h"



Room::Room(int x2, int y2, Room* r)
{
	x = x2;
	y = y2;

	parent = r;
}


Room::~Room()
{
}

string Room::getDescription()
{
	return description;
}

void Room::setDescription(string desc)
{
	description = desc;
}

// compute opposite node given that it is in the other direction from the parent
Room* Room::opposite()
{
	if ((x - parent->getX()) != 0)
		return new Room(x + (x - parent->getX()), y, this);
	if ((y - parent->getY()) != 0)
		return new Room(x, y + (y - parent->getY()), this);
	return 0;
}