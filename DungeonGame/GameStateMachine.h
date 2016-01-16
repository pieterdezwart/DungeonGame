#pragma once
#include "GameState.h"
#include <vector>

class GameStateMachine
{
public:
	void pushState(GameState* state);
	void changeState(GameState* state);
	void popState();

	void update();
	void view();

	GameState* currentState() { return gameStates.back(); }

private:
	std::vector<GameState*> gameStates;
};

