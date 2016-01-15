#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Dungeon.h"
#include "Enemy.h"
#include "Hero.h"
#include "GameStateMachine.h"

using namespace std;

class Trap;
class Item;

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
	void update();
	void view();

	string getRoom();

	vector<string> getRoomSizes();
	vector<string> getRoomStates();
	vector<string> getRoomProperties();
	vector<string> getRoomLights();

	string getRandStringElem(vector<string> array);

	string genRoomDescription();

	void genEnemies(Room* location, Map* m);

	void genTraps(Room* location, Map* m);

	void genItems(Room* location, Map* m);

	Hero* getHero() { return hero; };
	Dungeon* getDungeon() { return dungeon; };

	vector<Enemy*> getEnemies() { return enemies; }

	void displayHeader();

	GameStateMachine* getFSM() { return gameStateMachine; }

private:
	// Private constructor
	Game() {};

	// Stop the compiler generating methods of copy the object
	Game(Game const&) = delete;
	void operator=(Game const&) = delete;

	vector<string> roomSize, roomState, roomProperties, roomLight;
	
	vector<Enemy*> enemies; // contains all the enemies from the text file
	vector<Trap*> traps; // contains all the traps from the text file
	vector<Item*> items; // contains all the items from the text file

	Dungeon* dungeon = nullptr;

	Hero* hero = nullptr;

	void loadRoomFile(string file);

	void loadEnemiesFile(string file);

	void loadTrapFile(string file);

	void loadItemFile(string file);

	vector<string> Game::split(string str, char delim);

	GameStateMachine* gameStateMachine;

};

