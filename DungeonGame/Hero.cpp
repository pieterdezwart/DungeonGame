#include "Hero.h"
#include "Room.h"
#include "Game.h"
#include <vector>
#include "MenuState.h"

Hero::~Hero()
{
}

void Hero::setLocation(Room* room)
{
	location = room; 
	x = room->getX(); 
	y = room->getY(); 
	room->setExplored(true);
	vector<Trap*> traps = room->getTraps();
	if (traps.size() > 0)
	{
		for (Trap* trap : traps)
		{
			if ((rand() % 100 > perception + 20) && trap->enabled())
			{
				health = -trap->getAttack();
				ostringstream os;
				os << "A trap goes off in the room! You take " << trap->getAttack() << " damage\n";
				string s = os.str();
				Game::getInstance().setMessage(s);
				trap->disable();
			}
			else {
				Game::getInstance().setMessage("You used your perception skill to spot and disable a trap in the room.\n");
				perception++;
				trap->disable();
			}
		}
	}
}

void Hero::search()
{

	std::cout << "Items:\n";
	if (location->getItems().size() == 0)
		std::cout << "The room is empty\n\n";
	else
	{
		std::cout << "You found: ";
		bool hasPrev = false;
		// temp display
		for (Item* item : location->getItems())
		{
			if (hasPrev) cout << ", ";
			std::cout << item->getName();
			addToInventory(item);
			hasPrev = true;
		}

		std::cout << std::endl << std::endl;
	}
	addPerception(1);
}

bool Hero::move(string direction)
{
	if(location->getEdges().count(direction) > 0)
		if (location->getEdge(direction) != nullptr)
		{
			Room* next = location->getEdge(direction);
			setLocation(next);
			if (direction == "up" || direction == "down")
			{
				Game::getInstance().getDungeon()->setCurrentMap(getLocation()->getMap());

				if (direction == "down" && location->getMap()->getLevel() == 10)
				{
					Game::getInstance().setMessage("You have reached the end. You will now return to the main menu.");
					Game::getInstance().save();
					Game::getInstance().getFSM()->changeState(new MenuState());
				}
			}
			return true;
		}
	return false;
}

void Hero::addExp(int x)
{
	experience += x;

	if (experience >= requiredXp)
		levelUp();
}

void Hero::printStats()
{
	cout << "Hero's stats:\n";
	cout << "Level: \t" << getLevel() << "\n";
	cout << "Health: \t" << getHealth() << "\n";
	cout << "Attack: \t" << getAttack() << "\n";
	cout << "Defense: \t" << getDefense() << "\n";
	cout << "Perception: \t" << perception << "\n";
	cout << "Experience: \t" << experience << "/" << requiredXp << "\n";
}

void Hero::useItem(Item* i)
{
	if (i->getAttack() > 0) setWeapon(i);
	if (i->getDefense() > 0) setShield(i);
	if (health > 0) usePotion(i);
}

void Hero::levelUp()
{
	level++;

	if (level > 1)
	{
		attack = (attack * level) * 1.2;
		defense = (defense * level) * 1.2;
		maxHealth = (maxHealth * level) * 1.2;
		health = maxHealth;
		requiredXp = (requiredXp * level) * 1.2;
		experience = 0;
	}

	Game::getInstance().setMessage("You have leveled up. Your stats have increased.\n");
}

void Hero::rest()
{
	if (location->getEnemies().size() > 0)
	{
		Game::getInstance().setMessage("Can't rest when enemies are nearby");
	}
	else
	{
		health = health + (0.1 * maxHealth);

		Game::getInstance().setMessage("You rest and gain some health");
	}
}

void Hero::usePotion(Item* i)
{
	inventory.erase(std::remove(inventory.begin(), inventory.end(), i), inventory.end());
}