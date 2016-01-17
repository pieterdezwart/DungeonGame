#include "Hero.h"
#include "Room.h"
#include "Game.h"
#include <vector>

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

void Hero::setLocation(Room* room)
{
	location = room; 
	x = room->getX(); 
	y = room->getY(); 
	room->setExplored(true);
	vector<Trap*> traps = room->getTraps();
	if (traps.size() > 0)
	{
		for (Trap* trap : traps)
		{
			if ((rand() % 100 > perception + 20) && trap->enabled())
			{
				health = -trap->getAttack();
				ostringstream os;
				os << "A trap goes off in the room! You take " << trap->getAttack() << " damage\n";
				string s = os.str();
				Game::getInstance().setMessage(s);
				trap->disable();
			}
			else {
				Game::getInstance().setMessage("You used your perception skill to spot and disable a trap in the room.\n");
				perception++;
				trap->disable();
			}
		}
	}
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
			setLocation(next);
			if (direction == "up" || direction == "down")
			{
				Game::getInstance().getDungeon()->setCurrentMap(getLocation()->getMap());
			}
			return true;
		}
	return false;
}

void Hero::printStats()
{
	cout << "Hero's stats:\n";
	cout << "Health: \t" << health << "\n";
	cout << "Attack: \t" << attack << "\n";
	cout << "Perception: \t" << perception << "\n";
}