#include "InputHandler.h"
#include "Game.h"
#include <string>

void InputHandler::handleInput(string input)
{
	if (input == "move")
	{
		InputHandler::move();
	}
	else if (input == "map")
	{
		Game::getInstance().getDungeon()->currentMap()->display(Game::getInstance().getHero()->getLocation());
	}
}

string InputHandler::getOptions()
{
	bool fighting = false;
	return (fighting) ? "[attack:flee:potion:item]" : "[look:search:rest:inventory:map:stats:move]";
}

string InputHandler::moveDirections()
{
	string ret = "[";
	Room* r = Game::getInstance().getHero()->getLocation();
	bool prev = false;
	for (auto const& kv : r->getEdges())
	{
		if (kv.second == nullptr) continue;
		if (prev) ret = ret + ":";
		prev = true;
		ret = ret + kv.first;
	}
	ret = ret + "]";
	return ret;
}

void InputHandler::move()
{
	cout << InputHandler::moveDirections() << "\n";
	string dir;
	cin >> dir;
	if (!Game::getInstance().getHero()->move(dir))
	{
		cout << "You run in to a wall, try again \n";
		move();
	}
	system("cls");
	cout << Game::getInstance().getRoom() << "\n"; //print room description
}