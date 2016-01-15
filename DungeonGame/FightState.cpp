#include "FightState.h"
#include <iostream>
#include "Game.h"

const std::string FightState::stateID = "FIGHT";

void FightState::update()
{
	// TODO: hero attacks an enemy picked from list

	// TODO: enemies should not attack on entering fight state

	int attack = 0;

	for (Enemy* enemy : Game::getInstance().getHero()->getLocation()->getEnemies())
	{
		// temp attack state
		// TODO: every enemy attacks and does an attack roll, save all actions in list for display

		attack += enemy->getAttack();
	}

	int health = Game::getInstance().getHero()->getHealth();

	health = health - attack;


	Game::getInstance().getHero()->setHealth(health);
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
