#include "Game.h"
#include <ctime>

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
