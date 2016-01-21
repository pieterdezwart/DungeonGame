#include "Dungeon.h"



Dungeon::Dungeon()
{
	//map = new Map(10, 10);
	//Map* prevMap = map;
	//for (size_t i = 1; i < 9; i++)
	//{
	//	prevMap = new Map(10, 10, prevMap);
	//}

	for (int i = 0; i < 10; i++)
	{
		if (i == 0)
			mapList.push_back(new Map(10, 10, i+1));
		else
			mapList.push_back(new Map(10, 10, i+1, mapList.at(i - 1)));
	}

	map = mapList.at(0);
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
