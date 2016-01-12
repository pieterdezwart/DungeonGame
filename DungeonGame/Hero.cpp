#include "Hero.h"
#include "Room.h"


Hero::Hero(Room* start)
{
	setLocation(start);
}


Hero::~Hero()
{
}


void Hero::look()
{
	cout << "Je kijkt om je heen \n";
	cout << "Beschrijving " << location->getDescription() << "\n";
	cout << "Uitgangen: " << location->getExitStrings() << "\n";
	cout << "pos" << x << "," << y << "\n";
}

void Hero::search()
{

}

void Hero::move(string direction)
{
	if (location->getEdge(direction))
	{
		Room* next = location->getEdge(direction);
		setLocation(next);
	}
}
