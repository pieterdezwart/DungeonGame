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

class Map
{
public:
	Map(int width, int height);
	~Map();

	void display();

	void generateMap();
	void generateMapOld();

private:
	int x, y;

	vector<vector<Room*>> grid2;

	char *grid; // grid char array

	Room* startRoom = nullptr;
};

