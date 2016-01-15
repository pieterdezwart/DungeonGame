#include "ExploreState.h"
#include "Game.h"
#include <iostream>

const std::string ExploreState::stateID = "EXPLORE";

void ExploreState::update()
{
}

void ExploreState::view()
{
	if (Game::getInstance().getHero()->getLocation()->getEnemies().size() > 0)
	{
		std::cout << "[attack:flee:search:inventory:map:stats]\n";
	}
	else
		std::cout << "[look:search:rest:inventory:map:stats:move]\n";
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
