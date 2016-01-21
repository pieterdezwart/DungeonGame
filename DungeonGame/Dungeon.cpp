#include "Dungeon.h"
#include "Game.h"


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

	// get boss enemies
	vector<Enemy*> bosses;
	for (Enemy* enemy : Game::getInstance().getEnemies())
	{
		if (enemy->getBoss()) bosses.push_back(enemy);
	}

	// copy the object and create new pointer to object
	Enemy* enemy1 = new Enemy(*bosses.at(rand() % (bosses.size() - 1)));
	enemy1->setLocation(mapList.at(4)->getExit());
	enemy1->setLevel(mapList.at(4)->getLevel());
	enemy1->boostStats();

	// add boss to level 5
	mapList.at(4)->addEnemy(enemy1);

	// copy the object and create new pointer to object
	Enemy* enemy2 = new Enemy(*bosses.at(rand() % (bosses.size() - 1)));
	enemy2->setLocation(mapList.at(9)->getExit());
	enemy2->setLevel(mapList.at(9)->getLevel());
	enemy2->boostStats();

	// add boss to level 10
	mapList.at(9)->addEnemy(enemy2);
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
