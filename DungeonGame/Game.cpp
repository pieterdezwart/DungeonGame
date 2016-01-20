#include "Game.h"
#include "Trap.h"
#include "Item.h"
#include <ctime>

#include "FileLoader.h"
#include "InputHandler.h"
#include "ExploreState.h"
#include "MenuState.h"


void Game::init()
{
	srand(time(NULL)); // random number seed

	//loadHeroFile("hero.txt");

	//loadRoomFile("room.txt");

	FileLoader* fileLoader = new FileLoader();

	//loadEnemiesFile("Resources/enemy.txt");

	//loadTrapFile("Resources/trap.txt");

	//loadItemFile("Resources/item.txt");

	// test enemies
	for (Enemy* enemy : enemies)
	{
		cout << enemy->getName() << ", " << enemy->getAttack() << ", " << enemy->getHealth() << ", " << enemy->getExperience() << ", " << enemy->getLevel() << endl;
	}

	// test traps
	for (Trap* trap : traps)
	{
		cout << trap->getName() << ", " << trap->getAttack() << endl;
	}

	// test items
	for (Item* item : items)
	{
		cout << item->getName() << ", " << item->getAttack() << endl;
	}

	dungeon = new Dungeon();

	Room* startRoom = dungeon->currentMap()->getStartRoom();

	hero = new Hero(startRoom);

	gameStateMachine = new GameStateMachine();
	gameStateMachine->changeState(new ExploreState());

	//vector<Enemy*> enemies2 = dungeon->currentMap()->getEnemies();

	//for (Enemy* enemy : enemies2)
	//{
	//	cout << enemy->getName() << ", Room: " << enemy->getLocation()->getX() << "," << enemy->getLocation()->getY() << endl;
	//}

	//vector<Trap*> traps2 = dungeon->currentMap()->getTraps();

	//for (Trap* trap : traps2)
	//{
	//	cout << trap->getName() << ", Room: " << trap->getLocation()->getX() << "," << trap->getLocation()->getY() << endl;
	//}

	//vector<Item*> items2 = dungeon->currentMap()->getItems();

	//for (Item* item : items2)
	//{
	//	cout << item->getName() << ", Room: " << item->getLocation()->getX() << "," << item->getLocation()->getY() << endl;
	//}
}

void Game::gameLoop()
{
	bool playing = true;
	bool clear = true;
	string input = "";
	while (playing)
	{
		if(clear) system("cls"); // clear the screen

		displayHeader();
		displayMessage();
		update();
		view();

		clear = InputHandler::getInstance().handleInput();
	}

}

void Game::update()
{
	gameStateMachine->update();
}

void Game::view()
{
	gameStateMachine->view();
}



string Game::getRoom() {
	return hero->getLocation()->getDescription();
}

vector<string> Game::getRoomSizes()
{
	return roomSize;
}

vector<string> Game::getRoomStates()
{
	return roomState;
}

vector<string> Game::getRoomProperties()
{
	return roomProperties;
}

vector<string> Game::getRoomLights()
{
	return roomLight;
}

string Game::getRandStringElem(vector<string> array)
{
	int r = rand() % (array.size() - 1);

	return array.at(r);
}

string Game::genRoomDescription()
{
	string description = "Het is een ";

	string size = getRandStringElem(roomSize);

	if (size == "groot") 
		size = "grote"; 
	else 
		size += "e";

	string state = getRandStringElem(roomState);

	state += "e";

	description += size + " " + state + " kamer.";

	string property = getRandStringElem(roomProperties);

	if (property == "tafel met 4 stoelen")
		description += "In het midden staat een " + property + ".";
	if (property == "een bed")
		description += "In de hoek staat " + property + ".";
	if (property == "leeg")
		description += "Het is een lege ruimte.";

	string light = getRandStringElem(roomLight);

	description += "Hij wordt verlicht door " + light + ".";

	return description;
}

void Game::genEnemies(Room* location, Map* m)
{
	// per room the chance of enemies is 40%?
	int roll = rand() % 100;

	if (roll > 60)
	{
		// now roll for number of enemies
		//while ( roll != 0)
		//{
		//	roll = rand() % 3;
		//}

		roll = rand() % 3;

		// pick a random type for each enemy
		for (int i = 0; i < roll; i++)
		{
			// copy the object and create new pointer to object
			Enemy* enemy = new Enemy(*enemies.at(rand() % (enemies.size() - 1)));
			enemy->setLocation(location);

			//dungeon->currentMap()->display();
			//dungeon->currentMap()->addEnemy(enemy);
			m->addEnemy(enemy);

			//delete enemy;
		}

	}
}

void Game::genTraps(Room* location, Map* m)
{
	// per room the chance of a trap is 10%?
	int roll = rand() % 100;

	if (roll > 90)
	{
		// copy the object and create new pointer to object
		Trap* trap = new Trap(*traps.at(rand() % (traps.size() - 1)));
		trap->setLocation(location);

		//dungeon->currentMap()->addTrap(trap);
		m->addTrap(trap);
		//delete trap;

	}
}

void Game::genItems(Room* location, Map* m)
{
	// per room the chance of an item is 5%?
	int roll = rand() % 100;

	if (roll >= 0)
	{
		// copy the object and create new pointer to object
		Item* item = new Item(*items.at(rand() % (items.size() - 1)));
		item->setLocation(location);

		//dungeon->currentMap()->addItem(item);
		m->addItem(item);

		//delete item;

	}
}

void Game::displayHeader()
{
	cout << "=============================================" << endl;
	cout << "=		DUNGEON GAME		=" << endl;
	cout << "=============================================" << endl;
	cout << endl;
}

void Game::displayMessage()
{
	if (message != "")
	{
		cout << message;
	}
	message = "";
}