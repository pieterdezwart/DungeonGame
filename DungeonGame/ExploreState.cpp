#include "ExploreState.h"
#include "Game.h"
#include "InputHandler.h"
#include <iostream>

const std::string ExploreState::stateID = "EXPLORE";

void ExploreState::update()
{
}

void ExploreState::view()
{
	std::cout << "Level: ";
	std::cout << Game::getInstance().getDungeon()->currentMap()->getLevel() << std::endl << std::endl;

	std::cout << "Description:\n";
	std::cout << Game::getInstance().getHero()->getLocation()->getDescription() << std::endl << std::endl;

	std::cout << "Exits:\n";
	std::cout << InputHandler::getInstance().moveDirections() << std::endl << std::endl;

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
		std::cout << "[attack:inventory:map:stats:move]\n\n";
	}
	else
		std::cout << "[search:rest:inventory:map:stats:move]\n\n";
}

bool ExploreState::onEnter()
{
	return true;
}

bool ExploreState::onExit()
{
	return true;
}
