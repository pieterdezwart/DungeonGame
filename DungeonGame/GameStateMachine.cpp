#include "GameStateMachine.h"


void GameStateMachine::pushState(GameState * state)
{
	gameStates.push_back(state);
	gameStates.back()->onEnter(); // call the onEnter method of last inserted state
}

void GameStateMachine::changeState(GameState * state)
{
	if (!gameStates.empty())
	{
		// check if there are states in the array and if it matches the current state
		if (gameStates.back()->getStateID() == state->getStateID())
		{
			return; // do nothing
		}

		// state doesn't match, remove old state and add new state
		if (gameStates.back()->onExit())
		{
			delete gameStates.back(); // delete the state
			gameStates.pop_back(); // remove last element from array
		}
	}

	// push back our new state
	gameStates.push_back(state);

	// initialise it
	gameStates.back()->onEnter();
}

void GameStateMachine::popState()
{
	if (!gameStates.empty()) 
	{
		if (gameStates.back()->onExit()) // call onExit of last inserted state
		{
			delete gameStates.back(); // delete the state 
			gameStates.pop_back(); // remove last element from array
		}
	}
}

void GameStateMachine::update()
{
	if (!gameStates.empty())
		gameStates.back()->update();
}

void GameStateMachine::view()
{
	if (!gameStates.empty())
		gameStates.back()->view();
}
