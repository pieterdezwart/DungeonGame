#include "Enemy.h"
#include <iostream>
#include "GameStateMachine.h"
#include "EnemyStates.h"

//Enemy::Enemy(const Enemy & obj)
//{
//	std::cout << "Copy constructor allocating ptr." << std::endl;
//
//	name = "test";
//}

Enemy::Enemy(std::string n, int a, int h, int e, int l) : name(n), attack(a), health(h), experience(e), level(l)
{
	stateMachine = new GameStateMachine();
	stateMachine->changeState(new IdleState());

	maxHealth = health;
}

Enemy::~Enemy()
{
}

void Enemy::move()
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
