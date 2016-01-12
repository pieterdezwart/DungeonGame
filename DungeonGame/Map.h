#pragma once
#include "Room.h"
#include <vector>
#include <iostream>
#include <math.h>
#include <ctime>
#include <sstream>
#include <string>
#include <queue>
#include "Enemy.h"
#include "Item.h"
#include "Trap.h"

using namespace std;

class Map
{
public:
	Map(int width, int height);
	~Map();

	void display();

	void generateMap();


	Room* getStartRoom();

	vector<Enemy*> getEnemies() { return enemies; };
	void addEnemy(Enemy* enemy);
	vector<Enemy*> getEnemies(Room* location);
	bool removeEnemy(Enemy* enemy);

	vector<Trap*> getTraps() { return traps; };
	void addTrap(Trap* trap);
	vector<Trap*> getTraps(Room* location);
	bool removeTrap(Trap* trap);

	vector<Item*> getItems() { return items; };
	void addItem(Item* item);
	vector<Item*> getItems(Room* location);
	bool removeItem(Item* item);

private:
	int max_X, max_Y;

	vector<vector<Room*>> grid2;
	bool coordsExist(int x, int y) {
		return (x >= 0 && y >= 0 && x <= max_X && y <= max_Y);
	};
	char *grid; // grid char array

	Room* startRoom = nullptr;
	void randConnect(int x, int y);

	vector<Enemy*> enemies; // all the enemies in the map
	vector<Trap*> traps; // all the traps in the map
	vector<Item*> items; // all the items in the map
};

