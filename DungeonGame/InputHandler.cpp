#include "InputHandler.h"
#include "Game.h"
#include <string>
#include "FightState.h"
#include "Item.h"

bool InputHandler::handleInput()
{
	std::cout << "Action: "; 
	//std::cin >> input;

	std::getline(std::cin, input); // does not ignore whitespace

	if (Game::getInstance().getFSM()->currentState()->getStateID() == "MENU")
	{
		if (input == "new hero")
		{
			std::cout << "Warning, this will delete the current hero" << std::endl;
			std::cout << "[ok:back]" << std::endl;

			std::cin >> input;

			if(input == "ok") Game::getInstance().resetHero();
			else return true;

		}
		else if (input == "new game")
		{
			Game::getInstance().start();
		}
		else if (input == "exit")
		{
			exit(0);
		}
		else
		{
			std::cout << "Input not allowed" << std::endl;
			return false;
		}
		return true;
	}

	if (Game::getInstance().getFSM()->currentState()->getStateID() == "EXPLORE")
	{
		if (input == "move")
		{
			InputHandler::move();
		}
		if (input == "map")
		{
			Game::getInstance().getDungeon()->currentMap()->display(Game::getInstance().getHero()->getLocation());
			InputHandler::block();
		}
		if (input == "map-cheat")
		{
			Game::getInstance().getDungeon()->currentMap()->displayCheat(Game::getInstance().getHero()->getLocation());
			InputHandler::block();
		}
		if (input == "teleport-end")
		{
			Game::getInstance().getHero()->setLocation(Game::getInstance().getHero()->getLocation()->getMap()->getExit());
		}
		if (input == "attack")
		{
			Game::getInstance().getFSM()->changeState(new FightState());
		}
		if (input == "stats")
		{
			Game::getInstance().getHero()->printStats();
			InputHandler::block();
		}
		if (input == "inventory")
		{
			inventory();
		}
		if (input == "search")
		{
			Game::getInstance().getHero()->search();
			block();
		}
		if (input == "rest")
		{
			Game::getInstance().getHero()->rest();
			return false;
		}
		else
		{
			cout << "Input not allowed" << endl;
		}
		return true;
	}

	if (Game::getInstance().getFSM()->currentState()->getStateID() == "FIGHT")
	{
		if (input == "attack")
		{
			dynamic_cast<FightState*>(Game::getInstance().getFSM()->currentState())->pickEnemy();
		}
		if (input == "flee")
		{
			dynamic_cast<FightState*>(Game::getInstance().getFSM()->currentState())->attemptFlee();
		}

		if (input == "item")
		{
			inventory();
		}
		else
		{
			cout << "Input not allowed" << endl;
		}
		return true;
	}


}

string InputHandler::getOptions()
{
	if (Game::getInstance().getHero()->getLocation()->getEnemies().size() > 0)
	{
		return "[attack:search:inventory:map:stats:move]";
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
	//system("cls");
	//cout << Game::getInstance().getRoom() << "\n"; //print room description
}

void InputHandler::block()
{
	cout << getOptions() << "\n";
	handleInput();
}

void InputHandler::inventory()
{
	Hero* h = Game::getInstance().getHero();
	cout << "[0] Close inventory\n";
	int index = 1;
	for (Item* i : h->getInventory())
	{
		cout << "["<<index<<"] " << i->getName() << " " << "atk: " << i->getAttack() << ", def: " << i->getDefense() << ", hp: " << i->getHealth() << "\n";
		index++;
	}
	cin >> input;
	if (is_number(input))
	{
		int num = stoi(input);
		if (num == 0 || num > h->getInventory().size()) return;
		h->useItem(h->getInventory()[num-1]);
	}
	else {
		cout << "Input was not numerical, please try again \n";
		inventory();
	}
}