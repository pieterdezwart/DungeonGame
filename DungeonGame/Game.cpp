#include "Game.h"
#include "Trap.h"
#include "Item.h"
#include <ctime>
#include "InputHandler.h"
#include "ExploreState.h"

void Game::init()
{
	srand(time(NULL)); // random number seed

	loadRoomFile("room.txt");

	loadEnemiesFile("enemy.txt");

	loadTrapFile("trap.txt");

	loadItemFile("item.txt");

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

void Game::loadRoomFile(string file)
{
	ifstream input_file{ file };

	string line;

	int count = 1;

	while (getline(input_file, line))
	{
		if (count == 1)
			roomSize = split(line, ',');
		if (count == 2)
			roomState = split(line, ',');
		if (count == 3)
			roomProperties = split(line, ',');
		if (count == 4)
			roomLight = split(line, ',');

		count++;
	}

	for (string s : roomSize)
	{
		//cout << s << endl;
	}
}

void Game::loadEnemiesFile(string file)
{
	ifstream input_file{ file };

	string line;

	// for each new line in enemy.txt create a new enemy object
	while (getline(input_file, line))
	{
		vector<string> enemyProperties = split(line, ',');

		//cout << enemyProperties[0] << endl;

		enemies.push_back(new Enemy(enemyProperties.at(0), std::stoi(enemyProperties.at(1)), std::stoi(enemyProperties.at(2)), std::stoi(enemyProperties.at(3)), 1));

	}
}

void Game::loadTrapFile(string file)
{
	ifstream input_file{ file };

	string line;

	// for each new line in enemy.txt create a new enemy object
	while (getline(input_file, line))
	{
		vector<string> trapProperties = split(line, ',');

		//cout << enemyProperties[0] << endl;

		traps.push_back(new Trap(trapProperties.at(0), std::stoi(trapProperties.at(1))));

	}
}

void Game::loadItemFile(string file)
{
	ifstream input_file{ file };

	string line;

	// for each new line in enemy.txt create a new enemy object
	while (getline(input_file, line))
	{
		vector<string> trapProperties = split(line, ',');

		//cout << enemyProperties[0] << endl;

		items.push_back(new Item(trapProperties.at(0), std::stoi(trapProperties.at(1)), std::stoi(trapProperties.at(2)), std::stoi(trapProperties.at(3))));

	}
}

// split a string in string tokens by delimiter
vector<string> Game::split(string str, char delim)
{
	vector<string> tokens;
	stringstream ss(str);
	string item;

	while (getline(ss, item, delim)) {
		tokens.push_back(item);
	}

	return tokens;
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