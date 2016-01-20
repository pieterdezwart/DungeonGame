#include "Room.h"
#include "Game.h"
#include "Map.h"
#include "Item.h"

Room::Room(int x2, int y2, Map* m)
{
	description = Game::getInstance().genRoomDescription();

	edges["north"] = nullptr;
	edges["east"] = nullptr;
	edges["south"] = nullptr;
	edges["west"] = nullptr;
	edges["up"] = nullptr;
	edges["down"] = nullptr;

	x = x2;
	y = y2;

	//parent = r;
	map = m;

	Game::getInstance().genEnemies(this, m);
	Game::getInstance().genTraps(this, m);
	Game::getInstance().genItems(this, m);
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
	int ret = -2;
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

vector<Enemy*> Room::getEnemies()
{
	vector<Enemy*> roomEnemies;

	for (Enemy* enemy : Game::getInstance().getDungeon()->currentMap()->getEnemies())
	{
		if (this == enemy->getLocation())
		{
			roomEnemies.push_back(enemy);
		}
	}

	return roomEnemies;
}

vector<Trap*> Room::getTraps()
{
	vector<Trap*> roomTraps;

	for (Trap* trap : Game::getInstance().getDungeon()->currentMap()->getTraps())
	{
		if (this == trap->getLocation())
		{
			roomTraps.push_back(trap);
		}
	}

	return roomTraps;
}

vector<Item*> Room::getItems()
{
	vector<Item*> roomItems;

	for (Item* item : Game::getInstance().getDungeon()->currentMap()->getItems())
	{
		if (this == item->getLocation())
		{
			roomItems.push_back(item);
		}
	}

	return roomItems;
}