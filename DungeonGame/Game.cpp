#include "Game.h"
#include <ctime>

void Game::init()
{
	loadRoomFile("room.txt");

	loadEnemiesFile("enemy.txt");

	// test enemies
	for (Enemy* enemy : enemies)
	{
		cout << enemy->getName() << ", " << enemy->getAttack() << ", " << enemy->getHealth() << ", " << enemy->getExperience() << ", " << enemy->getLevel() << endl;
	}

	cout << endl;
	cout << "=============================================" << endl;
	cout << "=		DUNGEON GAME		=" << endl;
	cout << "=============================================" << endl;

	dungeon = new Dungeon();

	Room* startRoom = dungeon->currentMap()->getStartRoom();

	hero = new Hero(startRoom);


}

void Game::gameLoop()
{
	bool playing = true;

	string input = "";
	while (playing)
	{
		cin >> input;
		//CODE BELOW IS TEMPORARY TO TEST
		if (input == "move")
		{
			cout << "what direction \n";
			cin >> input;
			hero->move(input);
		}
		if (input == "cls")
		{
			system("cls");
		}
		getRoom();
	}
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

		cout << enemyProperties[0] << endl;

		enemies.push_back(new Enemy(enemyProperties.at(0), std::stoi(enemyProperties.at(1)), std::stoi(enemyProperties.at(2)), std::stoi(enemyProperties.at(3)), 1));

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

void Game::getRoom() {
	cout << hero->getLocation()->getDescription();
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
	srand((unsigned)time(NULL)); // seed based on current timestamp

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
