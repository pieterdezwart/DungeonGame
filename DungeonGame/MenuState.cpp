#include <iostream>

#include "MenuState.h"
#include "Game.h"

const std::string MenuState::stateID = "MENU";

void MenuState::update()
{


}

void MenuState::view()
{
	if (Game::getInstance().getHero() != nullptr)
	{
		std::cout << "Current hero:" << std::endl << std::endl;
		std::cout << "Name: " << Game::getInstance().getHero()->getName() << std::endl << std::endl;
		Game::getInstance().getHero()->printStats();
	}
	else
		std::cout << "No hero found. Please create a new hero." << std::endl << std::endl;

	std::cout << "\nPick an option:\n";

	if (Game::getInstance().getHero() == nullptr)
	{
		std::cout << "[new hero]\n";
	}
	else
		std::cout << "[new hero:new game]\n";
}

bool MenuState::onEnter()
{
	std::cout << "Entering MenuState";

	return true;
}

bool MenuState::onExit()
{
	std::cout << "Exiting MenuState";
	return true;
}
