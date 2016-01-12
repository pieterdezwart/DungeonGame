#include "Room.h"
#include "Game.h"
#include "Map.h"

Room::Room(int x2, int y2, Map* map)
{
	description = Game::getInstance().genRoomDescription();

	Game::getInstance().genEnemies(this, map);
	//Game::getInstance().genTraps(this, map);
	//Game::getInstance().genItems(this, map);

	edges["north"] = nullptr;
	edges["east"] = nullptr;
	edges["south"] = nullptr;
	edges["west"] = nullptr;

	x = x2;
	y = y2;

	//parent = r;
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


void Room::addEdge(string dir, Room* edge)
{
	auto combi = edges.find(dir);

	if (combi != edges.end()) {
		combi->second = edge;
	}
}

void Room::addEdge(Room* edge)
{
	if (x == edge->getX() && y < edge->getY()) addEdge("south", edge);
	if (x == edge->getX() && y > edge->getY()) addEdge("north", edge);
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
