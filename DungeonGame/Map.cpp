#include "Map.h"



Map::Map(int width, int height)
{
	//int grid[width][height];

	//Room* grid[10][10];

	char grid[10][10];

	char s[10];
	for (int i = 0; i < 10; i++)
	{
		//grid[0][i] = new Room();
		s[i] = 'X';

		//const char* grid[10][10];

		for (int x = 0; x < 10; x++)
		{
			grid[x][i] = *s;
			//strcpy(tab2, tmp.c_str());
		}
	}

	// select random point and open as start node
	srand((unsigned)time(0)); // activates the random generator
	startRoom = new Room(rand() % 10, rand() % 10, nullptr);
	grid[startRoom->getX()][startRoom->getY()] = 'S';


	// iterate through direct neighbors of node
	// and activate all the edges of the node
	vector<Room*> edges;
	for (int x = -1; x <= 1; x++)
		for (int y = -1; y <= 1; y++) {
			if (x == 0 && y == 0 || x != 0 && y != 0)
				continue;
			try {
				if (grid[startRoom->getX() + x][startRoom->getY() + y] == '.') continue;
			}
			catch (const std::exception& e) { // ignore ArrayIndexOutOfBounds
				continue;
			}
			// add eligible points to edges
			edges.push_back(new Room(startRoom->getX() + x, startRoom->getY() + y, startRoom));
		
	}

	Room* last = nullptr;

	// continue opening up wall sections while node on other side of wall
	// is wall (not explored)
	while (!edges.empty()) {

		// pick current node at random
		int temp = (int)(rand() % edges.size());
		Room* node = edges.at(temp);
		edges.erase(edges.begin() + temp);
		Room* op = node->opposite();
		try {
			// if both node and its opposite are walls
			if (grid[node->getX()][node->getY()] == 'X') {
				if (grid[op->getX()][op->getY()] == 'X') {

					// open path between the nodes
					grid[node->getX()][node->getY()] = '.';
					grid[op->getX()][op->getY()] = '.';

					// store last node in order to mark it later
					last = op;

					// iterate through direct neighbors of node, same as earlier
					for (int x = -1; x <= 1; x++)
						for (int y = -1; y <= 1; y++) {
							if (x == 0 && y == 0 || x != 0 && y != 0)
								continue;
							try {
								if (grid[op->getX() + x][op->getY() + y] == '.') continue;
							}
							catch (const std::exception& e) {
								continue;
							}
							edges.push_back(new Room(op->getX() + x, op->getY() + y, op));
						}
				}
			}
		}
		catch (const std::exception& e) { // ignore NullPointer and ArrayIndexOutOfBounds
		}

		// if algorithm has resolved, mark end node
		if (edges.empty())
			grid[last->getX()][last->getY()] = 'E';
	}



	// print final maze
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++)
			cout << grid[i][j];
		cout << endl;
	}

}


Map::~Map()
{
}


void Map::display()
{

}