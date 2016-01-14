#include "Dungeon.h"



Dungeon::Dungeon()
{
	map = new Map(10, 10);
	Map* prevMap = map;
	for (size_t i = 1; i < 9; i++)
	{
		prevMap = new Map(10, 10, prevMap);
	}
}


Dungeon::~Dungeon()
{
}

void Dungeon::generateMap()
{

}

Map* Dungeon::currentMap() 
{
	return map;
}
