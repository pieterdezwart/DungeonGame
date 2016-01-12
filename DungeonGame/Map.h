#pragma once
#include "Room.h"
#include <vector>
#include <iostream>
#include <math.h>
#include <ctime>
#include <sstream>
#include <string>
#include <queue>

using namespace std;

class Enemy;

class Map
{
public:
	Map(int width, int height);
	~Map();

	void display(Room* heropos);

	void generateMap();


	Room* getStartRoom();

	vector<Enemy*> getEnemies() { return enemies; };
	void addEnemy(Enemy* enemy);
	vector<Enemy*> getEnemies(Room* location);
	bool removeEnemy(Enemy* enemy);

private:
	int max_X, max_Y;

	vector<vector<Room*>> grid2;
	bool coordsExist(int x, int y) {
		return (x >= 0 && y >= 0 && x <= max_X && y <= max_Y);
	};
	char *grid; // grid char array

	Room* startRoom = nullptr;
	void randConnect(int x, int y);

	vector<Enemy*> enemies;
};

