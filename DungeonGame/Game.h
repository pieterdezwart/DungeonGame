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
	static Game& getInstance()
	{
		/* The only instance, guaranteed to be lazy initialized,
		guaranteed that it will be destroyed correctly */
		static Game instance;
		return instance;
	}

	void init();
	void gameLoop();

	void getRoom();
	void getActionList();

	vector<string> getRoomSizes();
	vector<string> getRoomStates();
	vector<string> getRoomProperties();
	vector<string> getRoomLights();

	string getRandStringElem(vector<string> array);

	string genRoomDescription();

private:
	// Private constructor
	Game() {};

	// Stop the compiler generating methods of copy the object
	Game(Game const&) = delete;
	void operator=(Game const&) = delete;

	vector<string> roomSize, roomState, roomProperties, roomLight;
	
	vector<Enemy*> enemies;

	Dungeon* dungeon = nullptr;

	Hero* hero = nullptr;

	void loadRoomFile(string file);

	void loadEnemiesFile(string file);

	vector<string> Game::split(string str, char delim);
};

