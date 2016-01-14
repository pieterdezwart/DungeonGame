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

bool Hero::move(string direction)
{
	if(location->getEdges().count(direction) > 0)
		if (location->getEdge(direction) != nullptr)
		{
			Room* next = location->getEdge(direction);
			setLocation(next);
			return true;
		}
	return false;
}
