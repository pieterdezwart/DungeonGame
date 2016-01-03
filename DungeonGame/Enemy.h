#pragma once
#include <string>

class Enemy
{
public:
	Enemy(std::string n, int a, int h, int e, int l) : name(n), attack(a), health(h), experience(e), level(l) {};
	~Enemy();

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
	int getExperience();
	int getLevel();

private:
	std::string name;

	int attack, defense, health, experience, level = 0;
};

