#pragma once
#include "GameState.h"

class ExploreState : public GameState
{
public:
	virtual void update();
	virtual void view();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return stateID; }

private:
	static const std::string stateID;
};

