#include "Map.h"
#include "Trap.h"


Map::Map(int width, int height)
{
	// Set up sizes. (HEIGHT x WIDTH)
	grid2.resize(height);
	for (int i = 0; i < height; ++i)
		grid2[i].resize(width);

	//cout << grid2[x].size;

	//grid = new char[width][height];

	//int grid[width][height];

	//Room* grid[10][10];

	max_X = width-1;
	max_Y = height-1;

	generateMap();

	//randomPaths();

	display();

}


Map::~Map()
{
}


void Map::display()
{
	for (int i = 0; i <= max_Y; i++) {
		for (int j = 0; j <= max_X; j++) {
			if (grid2[i][j] != nullptr) {

				//(grid2[i][j]->getEdge("west")) ? cout << "-" : cout << " "; 
				cout << grid2[i][j]->getType();
				(grid2[i][j]->getEdge("east")) ? cout << "-" : cout << " ";
			}
			else
				cout << "X ";
		}
		cout << endl;
		for (int j = 0; j <= max_X; j++) {
			if (grid2[i][j] != nullptr){
				(grid2[i][j]->getEdge("north")) ? cout << "| " : cout << "  ";
				//(grid2[i][j]->getEdge("north")) ? cout << "s" : cout << "  ";
			}
			else
				cout << " ";
		}
		cout << endl;
	}
}

void Map::generateMap()
{

	for (int i = 0; i <= max_Y; i++)
	{
		for (int x = 0; x <= max_X; x++)
		{
			Room* temp = new Room(x, i, nullptr);
			temp->setType('X');

			grid2[i][x] = temp;

			//grid[x][i] = *s;
			//strcpy(tab2, tmp.c_str());
		}
	}

	// select random point and open as start node
	srand((unsigned)time(0)); // activates the random generator
	startRoom = new Room(rand() % max_X, rand() % max_Y, nullptr);
	startRoom->setType('S'); // declare start room type
	startRoom->setDescription("Dit is de ingang van de kerker. De deur naar buiten is dicht.");
	grid2[startRoom->getY()][startRoom->getX()] = startRoom;

	for (int i = 0; i <= max_Y; i++)
	{
		for (int x = 0; x <= max_X; x++)
		{
			randConnect(x, i);
		}
	}
	

}

void Map::randConnect(int x, int y)
{
	int i = y;
	Room* r = grid2[i][x];
	int edgesPossible = 0;
	edgesPossible = (i > 0 && i < max_Y) ? edgesPossible += 2 : edgesPossible += 1;
	edgesPossible = (x > 0 && x < max_X) ? edgesPossible += 2 : edgesPossible += 1;
	if (r->numEdges() < edgesPossible)
	{
		int dirs[4][2] = { {1,0},{0,1}, {-1,0},{0,-1} };
		int index = rand() % 4;
		//cout << "r" << index << "\n";
		for (int i = 0; i < 4; i++)
		{
			//cout << index << "\n";
			int coords[2] = {y + dirs[index][1], x + dirs[index][0] };
			if (coordsExist(coords[0],coords[1]))
			{
				Room* rn = grid2[coords[0]][coords[1]];
				if (!rn->isLinked(r))
				{
					r->addEdge(rn);
					rn->addEdge(r);
					return;
				}
			}
			index = (index < 3) ? index+1 : 0;
		}
	}
}

Room* Map::getStartRoom()
{
	for (int i = 0; i <= max_Y; i++)
	{
		for (int x = 0; x <= max_X; x++)
		{

			if (grid2[i][x]->getType() == 'S')
				return grid2[i][x];
		}
	}
}

void Map::addEnemy(Enemy * enemy)
{
	enemies.push_back(enemy);
}

vector<Enemy*> Map::getEnemies(Room * location)
{
	return enemies;
}


bool Map::removeEnemy(Enemy * enemy)
{
	return false;
}

void Map::addTrap(Trap * trap)
{
	traps.push_back(trap);
}

vector<Trap*> Map::getTraps(Room * location)
{
	return traps;
}

bool Map::removeTrap(Trap * trap)
{
	return false;
}

void Map::addItem(Item * item)
{
	items.push_back(item);
}

vector<Item*> Map::getItems(Room * location)
{
	return items;
}

bool Map::removeItem(Item * item)
{
	return false;
}
