#include "Enemy.h"
#include <iostream>
#include "GameStateMachine.h"
#include "EnemyStates.h"
#include "Game.h"

Enemy::Enemy(std::string n, int a, int d, int h, int e, bool b) : name(n), attack(a), defense(d), health(h), experience(e), boss(b)
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

// increase enemy stats based on level
void Enemy::boostStats()
{
	if (level > 1)
	{
		attack = (attack * level) * 1.2;
		defense = (defense * level) * 1.2;
		health = (health * level) * 1.2;
		experience = (experience * level) * 1.2;

		maxHealth = health;
	}
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
