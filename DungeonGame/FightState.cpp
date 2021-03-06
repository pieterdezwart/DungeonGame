#include "FightState.h"
#include <iostream>
#include "Game.h"
#include "EnemyStates.h"
#include "ExploreState.h"
#include "MenuState.h"

const std::string FightState::stateID = "FIGHT";

void FightState::update()
{
	// TODO: enemies should not attack on entering fight state

	if (enemyAttack)
	{
		int attack = 0;

		for (auto enemy : enemyList)
		{
			// temp attack state
			// TODO: every enemy attacks and does an attack roll, save all actions in list for display

			attack += enemy.second->getAttack();

			enemiesResult += enemy.first + " attacks and does ";
			enemiesResult += std::to_string(enemy.second->getAttack()) + " damage.\n";
		}
		int roll = rand() % 2;
		if (roll > 1.5)
		{
			Game::getInstance().getHero()->addDefense(1);
		}
		attack -= (Game::getInstance().getHero()->getDefense() * roll);

		int health = Game::getInstance().getHero()->getHealth();

		health = health - attack;

		Game::getInstance().getHero()->setHealth(health);

		if (Game::getInstance().getHero()->getHealth() <= 0)
		{
			// TODO: need to implement dead state, reload hero etc.
			Game::getInstance().setHero(new Hero(Game::getInstance().getHero()->getName()));
			Game::getInstance().getFSM()->changeState(new MenuState());
		}
	}

	if (enemyList.size() == 0)
	{
		Game::getInstance().getFSM()->changeState(new ExploreState());
	}

}

void FightState::view()
{
	std::cout << "Fighting:\n";

	// temp display
	for (auto enemy : enemyList)
	{
		std::cout << enemy.first << ": ";
		std::cout << enemy.second->getHealth() << " of " << enemy.second->getMaxHealth() << std::endl;
	}

	std::cout << std::endl;

	if (enemyAttack)
	{
		std::cout << "Actions hero:\n";
		std::cout << heroResult << std::endl << std::endl;

		std::cout << "Actions enemies:\n";
		std::cout << enemiesResult << std::endl;
	}

	std::cout << "You have " << Game::getInstance().getHero()->getHealth() << " of "
		<< Game::getInstance().getHero()->getMaxHealth() << " life remaining.\n\n";

	std::cout << "Make a move.\n\n";
	if(!bossFight())
		std::cout << "[attack:flee:item]\n\n";
	else
		std::cout << "[attack:item]\n\n";

	enemyAttack = true; // enable enemy attacks after entering

	enemiesResult = "";
	heroResult = "";
}

void FightState::pickEnemy()
{
	std::cout << "Pick an enemy:\n";

	std::cout << "[";

	int size = 1;
	for (auto enemy : enemyList)
	{
		if (size != enemyList.size())
			std::cout << enemy.first << "|";
		else
			std::cout << enemy.first << "";

		size++;
	}

	std::cout << "]\n";

	std::string input;
	//std::cin.ignore();
	std::getline(std::cin, input);

	result(input);
}

void FightState::result(std::string input)
{
	// hero attacks
	int eHealth = enemyList.at(input)->getHealth();

	eHealth -= Game::getInstance().getHero()->getAttack();

	enemyList.at(input)->setHealth(eHealth);

	if (eHealth <= 0)
	{
		heroResult = "You killed " + input;
		Game::getInstance().getHero()->addExp(enemyList.at(input)->getExperience()); // if you kill an enemy add xp
		delete enemyList.at(input);
		enemyList.erase(input);
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
	return true;
}

void FightState::attemptFlee()
{
	if (bossFight())return;
	int roll = rand() % 100;
	if (roll > 50)
	{
		Game::getInstance().getFSM()->changeState(new ExploreState());
		Game::getInstance().setMessage("You have successfully fled from your enemies!\n");
	}
	else {
		Game::getInstance().setMessage("Your fleeing attempt failed!\n");
	}
}

bool FightState::bossFight()
{

	for (auto enemy : enemyList)
	{
		if(enemy.second->getBoss()) return true;
	}
	return false;
}