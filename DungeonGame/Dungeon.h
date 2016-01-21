#pragma once
#include "Map.h"
#include "Room.h"

class Dungeon
{
public:
	Dungeon();
	~Dungeon();

	void generateMap();

	Map* currentMap();
	void setCurrentMap(Map* m) { map = m; };
private: 
	Map* map = nullptr;

	// safer method i think
	vector<Map*> mapList;
};

