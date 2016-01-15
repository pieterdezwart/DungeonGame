#include "FightState.h"
#include <iostream>

const std::string FightState::stateID = "FIGHT";

void FightState::update()
{
}

void FightState::view()
{
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
