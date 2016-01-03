#include "Hero.h"



Hero::Hero()
{
}


Hero::~Hero()
{
}

void Hero::setLocation(Room* room)
{
	currentRoom = room;
}

Room* Hero::getLocation()
{
	return currentRoom;
}