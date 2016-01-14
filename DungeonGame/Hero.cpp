#include "Hero.h"
#include "Room.h"
#include "Game.h"

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
	addPerception(1);
}

bool Hero::move(string direction)
{
	if(location->getEdges().count(direction) > 0)
		if (location->getEdge(direction) != nullptr)
		{
			Room* next = location->getEdge(direction);
			if (!next->isExplored()) addPerception(1);
			setLocation(next);
			if (direction == "up" || direction == "down")
			{
				Game::getInstance().getDungeon()->setCurrentMap(getLocation()->getMap());
			}
			return true;
		}
	return false;
}
