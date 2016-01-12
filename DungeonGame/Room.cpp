#include "Room.h"
#include "Game.h"


Room::Room(int x2, int y2, Room* r)
{
	description = Game::getInstance().genRoomDescription();

	Game::getInstance().genEnemies(this);
	//Game::getInstance().genTraps(this);
	//Game::getInstance().genItems(this);

	edges["north"] = nullptr;
	edges["east"] = nullptr;
	edges["south"] = nullptr;
	edges["west"] = nullptr;

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
	/*
	if (parent->getY() > y)
		return new Room(x, 1 + parent->getY(), this);
	if (parent->getY() < y)
		return new Room(x, 1 - parent->getY(), this);
	if (parent->getX() > x)
		return new Room(1 + parent->getX(), y, this);
	if (parent->getX() < x)
		return new Room(1 - parent->getX(), y, this);
	*/

	if ((y - parent->getY()) != 0)
		return new Room(x, y + (y - parent->getY()), this);
	if ((x - parent->getX()) != 0)
		return new Room(x + (x - parent->getX()), y, this);

	return 0;
}

void Room::addEdge(string dir, Room* edge)
{
	auto combi = edges.find(dir);

	if (combi != edges.end()) {
		combi->second = edge;
	}
}

void Room::addEdge(Room* edge)
{
	if (x == edge->getX() && y > edge->getY()) addEdge("south", edge);
	if (x == edge->getX() && y < edge->getY()) addEdge("north", edge);
	if (x < edge->getX() && y == edge->getY()) addEdge("east", edge);
	if (x > edge->getX() && y == edge->getY()) addEdge("west", edge);
}

bool Room::isLinked(Room* r)
{
	for (auto const& kv : edges)
	{
		if (kv.second == r)
			return true;
	}
	return false;
}

string Room::randFreeEdge()
{
	string ret = "";
	string dirs[4] = { "north", "east", "south", "west" };
	while (ret == "" && numEdges() < 4)
	{
		int r = rand() % 4;
		if (edges.at(dirs[r]) == nullptr)
			ret = dirs[r];
	}
	return ret;
}

int Room::numEdges()
{
	int ret = 0;
	for (auto const& kv : edges)
	{
		if (kv.second != nullptr)
			ret++;
	}
	return ret;
}

Room* Room::getEdge(string dir)
{
	auto combi = edges.find(dir);

	if (combi != edges.end()) {
		return combi->second;
	}
}

void Room::setType(char c)
{
	type = c;
}

string Room::getExitStrings()
{
	string ret = "";
	for (auto const& kv : edges)
	{
		ret = ret + kv.first + " ";
	}
	return ret;
}
