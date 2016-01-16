#include "EnemyStates.h"
#include <iostream>

const std::string IdleState::stateID = "IDLE";

void IdleState::update()
{

}

void IdleState::view()
{

}

bool IdleState::onEnter()
{
	std::cout << "Entering IdleState";
	return true;
}

bool IdleState::onExit()
{
	std::cout << "Exiting IdleState";
	return true;
}


const std::string AttackState::stateID = "Attack";

void AttackState::update()
{

}

void AttackState::view()
{

}

bool AttackState::onEnter()
{
	std::cout << "Entering AttackState";
	return true;
}

bool AttackState::onExit()
{
	std::cout << "Exiting AttackState";
	return true;
}