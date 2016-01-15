#include "ExploreState.h"
#include "Game.h"
#include <iostream>

const std::string ExploreState::stateID = "EXPLORE";

void ExploreState::update()
{
}

void ExploreState::view()
{
	std::cout << "Description:\n";
	std::cout << Game::getInstance().getHero()->getLocation()->getDescription() << std::endl << std::endl;

	std::cout << "Exits:\n";
	std::cout << Game::getInstance().getHero()->getLocation()->getExitStrings() << std::endl << std::endl;

	std::cout << "Enemies:\n";
	if (Game::getInstance().getHero()->getLocation()->getEnemies().size() == 0)
		std::cout << "The room is empty\n\n";
	else
	{
		// temp display
		for (Enemy* enemy : Game::getInstance().getHero()->getLocation()->getEnemies())
		{
			std::cout << enemy->getName() << ", ";
		}

		std::cout << std::endl << std::endl;
	}

	std::cout << "Make a move.\n\n";

	if (Game::getInstance().getHero()->getLocation()->getEnemies().size() > 0)
	{
		std::cout << "[attack:flee:search:inventory:map:stats]\n\n";
	}
	else
		std::cout << "[look:search:rest:inventory:map:stats:move]\n\n";
}

bool ExploreState::onEnter()
{
	std::cout << "Entering ExploreState\n";
	return true;
}

bool ExploreState::onExit()
{
	std::cout << "Exiting ExploreState\n";
	return true;
}
