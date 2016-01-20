#include <iostream>

#include "MenuState.h"
#include "Game.h"

const std::string MenuState::stateID = "MENU";

void MenuState::update()
{


}

void MenuState::view()
{
	/*  options:
		[new hero]
		[load hero]
		[new game]
		//[continue game] -> if hero is loaded
	*/

	std::cout << "Pick an option:\n\n";

	if (Game::getInstance().getHero() != nullptr)
	{
		std::cout << "[new hero:new game]\n\n";
	}
	else
		std::cout << "[new hero:load hero:new game]\n\n";
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
