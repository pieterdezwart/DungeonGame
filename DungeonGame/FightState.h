#pragma once
#include "GameState.h"
#include <map>
#include "Enemy.h"

class FightState : public GameState
{
public:
	virtual void update();
	virtual void view();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return stateID; }

	void pickEnemy();
	void attemptFlee();
	bool bossFight();
	void result(std::string choice);

private:
	static const std::string stateID;

	bool enemyAttack = false; // disable enemy attacks on entering fight state
	std::map<std::string, Enemy*> enemyList;

	std::string heroResult;
	std::string enemiesResult;
};

