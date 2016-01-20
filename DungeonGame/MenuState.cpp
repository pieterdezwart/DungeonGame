#include "MenuState.h"
#include <iostream>

const std::string MenuState::stateID = "MENU";

void MenuState::update()
{


}

void MenuState::view()
{
	/*  options:
		[create new hero]
		[load hero]
		[delete hero]
		[start game]
		[continue game] -> if hero is loaded
	*/

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
