#include "InputHandler.h"
#include "Game.h"
#include <string>

void InputHandler::handleInput(string input)
{
	if (input == "move")
	{
		InputHandler::move();
	}
	if (input == "map")
	{
		Game::getInstance().getDungeon()->currentMap()->display(Game::getInstance().getHero()->getLocation());
	} 
	if (input == "teleport-end")
	{
		Game::getInstance().getHero()->setLocation(Game::getInstance().getHero()->getLocation()->getMap()->getExit());
	}
	if (input == "attack")
	{
		Game::getInstance().getHero()->setFighting(true);
	}
}

string InputHandler::getOptions()
{
	if (Game::getInstance().getHero()->getFighting()) {
		return "[attack:flee:potion:item]";
	}
	else if (Game::getInstance().getHero()->getLocation()->getEnemies().size() > 0)
	{
		return "[attack:flee:search:inventory:map:stats]";
	}
	else
	 return "[look:search:rest:inventory:map:stats:move]";
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