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
class FileLoader;

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

	void start();
	void resetHero();
	void save();

	string getRoom();

	void addRoomSize(std::string token) { roomSize.push_back(token); };
	void addRoomState(std::string token) { roomState.push_back(token); };
	void addRoomProperties(std::string token) { roomProperties.push_back(token); };
	void addRoomLight(std::string token) { roomLight.push_back(token); };
	void addRoomAtmosphere(std::string token) { roomAtmosphere.push_back(token); };
	void addRoomWall(std::string token) { roomWall.push_back(token); };

	void addEnemy(Enemy* enemy) { enemies.push_back(enemy); };
	void addBoss(Enemy* boss) { bosses.push_back(boss); }
	void addTrap(Trap* trap) { traps.push_back(trap); };
	void addItem(Item* item) { items.push_back(item); };

	vector<string> getRoomSizes() { return roomSize; }
	vector<string> getRoomStates() { return roomState; }
	vector<string> getRoomProperties() { return roomProperties; }
	vector<string> getRoomLights() { return roomLight; }
	vector<string> getRoomAtmosphere() { return roomAtmosphere; }
	vector<string> getRoomWall() { return roomWall; }

	string getRandStringElem(vector<string> array);

	string genRoomDescription();

	void genEnemies(Room* location, Map* m);

	void genTraps(Room* location, Map* m);

	void genItems(Room* location, Map* m);

	Hero* getHero() { return hero; };
	void setHero(Hero* h) { hero = h; }

	Dungeon* getDungeon() { return dungeon; };

	vector<Enemy*> getEnemies() { return enemies; }
	vector<Enemy*> getBosses() { return bosses; }
	vector<Item*> getItems() { return items; }

	void displayHeader();

	GameStateMachine* getFSM() { return gameStateMachine; }
	void setMessage(string msg) { message = msg;};
	void Game::displayMessage();
private:
	// Private constructor
	Game() {};

	// Stop the compiler generating methods of copy the object
	Game(Game const&) = delete;
	void operator=(Game const&) = delete;

	FileLoader* fileLoader = nullptr;

	vector<string> roomSize, roomState, roomProperties, roomLight, roomAtmosphere, roomWall;
	
	vector<Enemy*> enemies; // contains all the enemies from the text file
	vector<Enemy*> bosses; // contains all the bosses 
	vector<Trap*> traps; // contains all the traps 
	vector<Item*> items; // contains all the items 

	Dungeon* dungeon = nullptr;

	Hero* hero = nullptr;

	GameStateMachine* gameStateMachine;

	string message = "";

};

