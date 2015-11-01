#pragma once
#include "Room.h"
#include <vector>
#include <iostream>
#include <math.h>
#include <ctime>
#include <sstream>
#include <string>

using namespace std;

class Map
{
public:
	Map(int width, int height);
	~Map();

	void display();

private:
	//int width, height;

	Room* startRoom = nullptr;
};

