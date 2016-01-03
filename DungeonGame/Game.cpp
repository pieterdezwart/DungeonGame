#include "Game.h"


void Game::init()
{
	loadRoomFile("room.txt");

	cout << endl;
	cout << "=============================================" << endl;
	cout << "=		DUNGEON GAME		=" << endl;
	cout << "=============================================" << endl;

	dungeon = new Dungeon();

	//Room* startRoom = dungeon->currentMap()->getStartRoom();

	hero = new Hero();

	hero->setLocation(dungeon->currentMap()->getStartRoom()); // put hero in startRoom


}

void Game::gameLoop()
{
	bool playing = true;

	while (playing)
	{
		//getRoom();

		//getActionList();



		continue;
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
		cout << s << endl;
	}
}

void Game::loadEnemiesFile(string file)
{

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