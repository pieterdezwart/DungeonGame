#pragma once
#include <string>

class Room;
class GameStateMachine;

class Enemy
{
public:
	Enemy(std::string n, int a, int d, int h, int e, bool b);

	~Enemy();

	void setLocation(Room* room) { location = room; };
	Room* getLocation() { return location; };

	void move();

	void setName(std::string value);

	void setAttack(int value);
	void setDefense(int value);
	void setHealth(int value);
	void setExperience(int value);
	void setLevel(int value);

	std::string getName();

	int getAttack();
	int getDefense();
	int getHealth();
	int getMaxHealth() { return maxHealth; };
	int getExperience();
	int getLevel();

	GameStateMachine* getFSM() { return stateMachine; }

	void boostStats();

private:
	Room* location = nullptr;

	std::string name;

	int attack, defense, health, experience, level, maxHealth = 0;
	bool boss = false;

	GameStateMachine* stateMachine;

};

