#include "FightState.h"
#include <iostream>
#include "Game.h"

const std::string FightState::stateID = "FIGHT";

void FightState::update()
{
	for (Enemy* enemy : Game::getInstance().getHero()->getLocation()->getEnemies())
	{
		std::cout << enemy->getName() << ": ";
		std::cout << enemy->getHealth() << " of " << "MaxHealth\n";
	}
}

void FightState::view()
{
	// temp display
	for (Enemy* enemy : Game::getInstance().getHero()->getLocation()->getEnemies())
	{
		std::cout << enemy->getName() << ": ";
		std::cout << enemy->getHealth() << " of " << "MaxHealth\n";
	}

	std::cout << std::endl;

	std::cout << "You have " << Game::getInstance().getHero()->getHealth() << " of "
		      << Game::getInstance().getHero()->getMaxHealth() << " life remaining.\n\n";
	
	std::cout << "Make a move.\n\n";
	std::cout << "[attack:flee:potion:item]\n\n";
}

bool FightState::onEnter()
{
	std::cout << "Entering FightState";
	return true;
}

bool FightState::onExit()
{
	std::cout << "Exiting FightState";
	return true;
}
