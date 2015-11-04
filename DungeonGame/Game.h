#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Dungeon.h"
#include "Enemy.h"
#include "Hero.h"

using namespace std;

class Game
{
public:
	Game();
	~Game();

	void getRoom();
	void getActionList();

private:
	vector<string> roomSize, roomState, roomProperties, roomLight;
	
	vector<Enemy*> enemies;

	Dungeon* dungeon = nullptr;

	Hero* hero = nullptr;

	void loadRoomFile(string file);

	void loadEnemiesFile(string file);

	vector<string> Game::split(string str, char delim);
};

