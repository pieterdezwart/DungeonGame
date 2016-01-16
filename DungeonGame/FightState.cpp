#include "FightState.h"
#include <iostream>
#include "Game.h"
#include "EnemyStates.h"

const std::string FightState::stateID = "FIGHT";

void FightState::update()
{
	// TODO: hero attacks an enemy picked from list

	// TODO: enemies should not attack on entering fight state

	if (enemyAttack)
	{
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

}

void FightState::view()
{
	std::cout << "Fighting:\n";

	// temp display
	for (Enemy* enemy : Game::getInstance().getHero()->getLocation()->getEnemies())
	{
		std::cout << enemy->getName() << ": ";
		std::cout << enemy->getHealth() << " of " << enemy->getMaxHealth() << std::endl;
	}

	std::cout << std::endl;

	if (enemyAttack)
	{
		std::cout << "Actions hero:\n";
		std::cout << heroResult << std::endl;

		std::cout << "Actions enemies:\n";
		std::cout << enemiesResult << std::endl;
	}

	std::cout << "You have " << Game::getInstance().getHero()->getHealth() << " of "
		<< Game::getInstance().getHero()->getMaxHealth() << " life remaining.\n\n";

	std::cout << "Make a move.\n\n";
	std::cout << "[attack:flee:potion:item]\n\n";

	enemyAttack = true; // enable enemy attacks after entering
}

void FightState::pickEnemy()
{
	std::cout << "Pick an enemy:\n";

	std::cout << "[";

	for (auto enemy : enemyList)
	{
		std::cout << enemy.first << "|";
	}

	std::cout << "]\n";

	std::string input;
	std::cin.ignore();
	std::getline(std::cin, input);

	result(input);
}

void FightState::result(std::string input)
{
	enemiesResult = "";
	heroResult = "";

	// hero attacks
	int eHealth = enemyList.at(input)->getHealth();

	eHealth -= Game::getInstance().getHero()->getAttack();

	enemyList.at(input)->setHealth(eHealth);

	if (eHealth <= 0)
	{
		heroResult = "You killed " + input;
		delete enemyList.at(input);
	}
	else
	{
		heroResult = "You attack " + input;
		heroResult += " and do ";
		heroResult += std::to_string(Game::getInstance().getHero()->getAttack()) + " damage.";
	}

	// enemies attack
}

bool FightState::onEnter()
{
	std::cout << "Entering FightState";

	// for each unique enemy type increase counter
	for (int i = 0; i < Game::getInstance().getHero()->getLocation()->getEnemies().size(); i++)
	{
		int counter = 1;

		if (i > 0 && Game::getInstance().getHero()->getLocation()->getEnemies().at(i)->getName() ==
			Game::getInstance().getHero()->getLocation()->getEnemies().at(i - 1)->getName())
			counter++;
		else
			counter = 1;

		std::string temp = Game::getInstance().getHero()->getLocation()->getEnemies().at(i)->getName() + " ";
		temp += std::to_string(counter);

		enemyList.insert({ temp, Game::getInstance().getHero()->getLocation()->getEnemies().at(i) });

		Game::getInstance().getHero()->getLocation()->getEnemies().at(i)->getFSM()->changeState(new AttackState());
	}

	return true;
}

bool FightState::onExit()
{
	std::cout << "Exiting FightState";
	return true;
}
