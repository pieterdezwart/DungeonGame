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
	Map(int width, int height, int l);
	Map(int width, int height, int l, Map* prev);
	~Map();

	void display(Room* heropos);
	void displayCheat(Room* heropos);

	void generateMap(Room* prevLevel);


	Room* getStartRoom() { return startRoom; };
	Room* getExit() {return exit; };

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
	bool removeItem(Item* item);
	int getLevel() { return level; };
private:
	int max_X, max_Y;

	vector<vector<Room*>> grid2;
	bool coordsExist(int x, int y) {
		return (x >= 0 && y >= 0 && x <= max_X && y <= max_Y);
	};
	char *grid; // grid char array

	Room* startRoom = nullptr;
	Room* exit = nullptr;
	void randConnect(int x, int y);
	string getLegend();

	vector<Enemy*> enemies; // all the enemies in the map
	vector<Trap*> traps; // all the traps in the map
	vector<Item*> items; // all the items in the map
	int level;
};

