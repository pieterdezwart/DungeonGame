#include "Map.h"
#include "Game.h"

Map::Map(int width, int height)
{
	// Set up sizes. (HEIGHT x WIDTH)
	grid2.resize(height);
	for (int i = 0; i < height; ++i)
		grid2[i].resize(width);

	max_X = width - 1;
	max_Y = height - 1;
	generateMap(nullptr);
	level = 0;
}

Map::Map(int width, int height, Map* prev)
{
	// Set up sizes. (HEIGHT x WIDTH)
	grid2.resize(height);
	for (int i = 0; i < height; ++i)
		grid2[i].resize(width);

	max_X = width-1;
	max_Y = height-1;
	generateMap(prev->getExit());
	level = prev->getLevel() + 1;
}


Map::~Map()
{
}


void Map::display(Room* heropos)
{
	cout << "\n";
	for (int i = 0; i <= max_Y; i++) {
		for (int j = 0; j <= max_X; j++) {
			Room* r = grid2[i][j];
			if (r != nullptr) {

				//(grid2[i][j]->getEdge("west")) ? cout << "-" : cout << " "; 
				if (r == heropos)
					cout << "H";
				else
					(r->isExplored()) ? cout << r->getType() : cout << " ";
				(r->getEdge("east") && (r->isExplored() || r->getEdge("east")->isExplored())) ? cout << "-" : cout << " ";
			}
			else
				cout << "  ";
		}
		cout << endl;
		for (int j = 0; j <= max_X; j++) {
			Room* r = grid2[i][j];
			if (r != nullptr){
				if (r->getEdge("south") && r->isExplored())
					cout << "| ";
				else
				{
					if (coordsExist(i + 1, j))
					{
						Room* r2 = grid2[i+1][j];
						if (r2->getEdge("north") && r2->isExplored())
						{
							cout << "| ";
						}
						else
							cout << "  ";
					}
					else
						cout << "  ";
				}
				//(grid2[i][j]->getEdge("north")) ? cout << "s" : cout << "  ";
			}
			else
				cout << " ";
		}
		cout << endl;
	}
	cout << getLegend();
}
void Map::displayCheat(Room* heropos)
{
	cout << "\n";
	for (int i = 0; i <= max_Y; i++) {
		for (int j = 0; j <= max_X; j++) {
			Room* r = grid2[i][j];
			if (r != nullptr) {

				//(grid2[i][j]->getEdge("west")) ? cout << "-" : cout << " "; 
				if (r == heropos)
					cout << "H";
				else
					cout << r->getType();
				(r->getEdge("east")) ? cout << "-" : cout << " ";
			}
			else
				cout << "  ";
		}
		cout << endl;
		for (int j = 0; j <= max_X; j++) {
			Room* r = grid2[i][j];
			if (r != nullptr) {
				if (r->getEdge("south"))
					cout << "| ";
				else
				{
					if (coordsExist(i + 1, j))
					{
						Room* r2 = grid2[i + 1][j];
						if (r2->getEdge("north"))
						{
							cout << "| ";
						}
						else
							cout << "  ";
					}
					else
						cout << "  ";
				}
				//(grid2[i][j]->getEdge("north")) ? cout << "s" : cout << "  ";
			}
			else
				cout << " ";
		}
		cout << endl;
	}
	cout << getLegend();
}

string Map::getLegend()
{
	string ret = "";
	ret = ret + "Legenda:\n";
	ret = ret + ":- : Hallways\n";
	ret = ret + "S  : Starting location\n";
	ret = ret + "X  : Room\n";
	ret = ret + "U  : Stairs down\n";
	ret = ret + "D  : Stairs up\n";
	ret = ret + "H  : Hero's location\n";
	return ret;
}

void Map::generateMap(Room* prevLevel)
{

	for (int i = 0; i <= max_Y; i++)
	{
		for (int x = 0; x <= max_X; x++)
		{
			Room* temp = new Room(x, i, this);
			temp->setType('X');

			grid2[i][x] = temp;

			//grid[x][i] = *s;
			//strcpy(tab2, tmp.c_str());
		}
	}

	//
	exit = new Room(rand() % max_X, rand() % max_Y, this);
	exit->setType('U'); // declare start room type
	grid2[exit->getY()][exit->getX()] = exit;

	// select random point and open as start node
	srand((unsigned)time(0)); // activates the random generator
	if (prevLevel == nullptr)
	{
		startRoom = new Room(rand() % max_X, rand() % max_Y, this);
		startRoom->setType('S'); // declare start room type
		startRoom->setDescription("Dit is de ingang van de kerker. De deur naar buiten is dicht.");
	}
	else {
		startRoom = new Room(prevLevel->getX(), prevLevel->getY(), this);
		startRoom->setType('D'); // declare start room type
	}
	grid2[startRoom->getY()][startRoom->getX()] = startRoom;

	for (int i = 0; i <= max_Y; i++)
	{
		for (int x = 0; x <= max_X; x++)
		{
			randConnect(x, i);
		}
	}

	if (prevLevel != nullptr)
	{
		startRoom->addEdge("down", prevLevel);
		prevLevel->addEdge("up", startRoom);
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

bool Map::removeItem(Item * item)
{
	return false;
}
