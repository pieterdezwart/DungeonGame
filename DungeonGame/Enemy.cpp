#include "Enemy.h"


Enemy::~Enemy()
{
}

void Enemy::setName(std::string value)
{
	name = value;
}

void Enemy::setAttack(int value)
{
	attack = value;
}

void Enemy::setDefense(int value)
{
	defense = value;
}

void Enemy::setHealth(int value)
{
	health = value;
}

void Enemy::setExperience(int value)
{
	experience = value;
}

void Enemy::setLevel(int value)
{
	level = value;
}

std::string Enemy::getName()
{
	return name;
}

int Enemy::getAttack()
{
	return attack;
}

int Enemy::getDefense()
{
	return defense;
}

int Enemy::getHealth()
{
	return health;
}

int Enemy::getExperience()
{
	return experience;
}

int Enemy::getLevel()
{
	return level;
}
