#pragma once
#include "Map.h"
#include "Room.h"

class Dungeon
{
public:
	Dungeon();
	~Dungeon();

	void generateMap();

private: 
	Map* map = nullptr;
};

