#include "Map.h"



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

	x = width;
	y = height;

	generateMap();


}


Map::~Map()
{
}


void Map::display()
{
	/*
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++)
			cout << grid[i][j];
		cout << endl;
	}
	*/
}

/*
void breadth_first_search(Room* start)
{
	for (Room v : g.vertices)
	{
		v.distance = INFINITY;
		v.parent = nullptr;
	}
	
	s->color = GRAY;
	s->discovery = 0;
	s->parent = nullptr;
	std::queue<Vertex*> q;
	q.push(s);

	while (!q.empty()) {
		auto u = q.front();
		q.pop();
	
		for (auto v : G.adjacent[u->id])) 
		{
			if (v->color == WHITE) {
				v->color = GRAY;
				v->discovery = u->discovery + 1;
				v->parent = u;
				q.push(v);
			}
		}
		u->color = BLACK;
	}
}
*/

/*
void bfs(Room* start)
{

	queue<Room*> q; // QUEUE
	q.push(start);


	while (!q.empty())
	{
		temp = q.front(); // Front element from Queue
		q.pop();
		int status[temp] = 1; // marked as visited , 0 means unvisited
		cout << temp << endl; // visited element
		for (it = list[temp].begin(); it != list[temp].end(); it++)
		{
			j = *it;
			if (status[j] == 0)
			{
				q.push(j);
				status[j] = 2;    // means that it is in queue        
			}
		}

	}
}
*/

void Map::generateMap()
{
	//char grid[20][20];

	/*
	char s[20];
	for (int i = 0; i < 20; i++)
	{
		//grid[0][i] = new Room();
		s[i] = 'X';

		//const char* grid[10][10];

		for (int x = 0; x < 20; x++)
		{
			grid[x][i] = *s;
			//strcpy(tab2, tmp.c_str());
		}
	}
	*/

	// select random point and open as start node
	srand((unsigned)time(0)); // activates the random generator
	startRoom = new Room(rand() % x-1, rand() % y-1, nullptr);
	startRoom->setType('S'); // declare start room type
	grid2[startRoom->getX()][startRoom->getY()] = startRoom;


	// iterate through direct neighbors of node
	// and activate all the edges of the node
	vector<Room*> frontier;
	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {
			if (x == 0 && y == 0 || x != 0 && y != 0)
				continue;
			try {
				if (grid2[startRoom->getX() + x][startRoom->getY() + y] != nullptr) continue;
			}
			catch (const std::exception& e) { // ignore ArrayIndexOutOfBounds
				continue;
			}
			// add eligible points to edges
			Room* temp = new Room(startRoom->getX() + x, startRoom->getY() + y, startRoom);

			if (temp->getY() == startRoom->getY() - 1)
				startRoom->addEdge("north", temp);
			if (temp->getX() == startRoom->getX() + 1)
				startRoom->addEdge("east", temp);
			if (temp->getY() == startRoom->getY() + 1)
				startRoom->addEdge("south", temp);
			if (temp->getX() == startRoom->getX() - 1)
				startRoom->addEdge("west", temp);

			frontier.push_back(temp);

		}
	}

	Room* current = startRoom;

	Room* last = nullptr;


	// continue opening up wall sections while node on other side of wall
	// is wall (not explored)
	while (!frontier.empty()) {

		// pick current node at random
		int temp = (int)(rand() % frontier.size());
		Room* node = frontier.at(temp);
		//current->addEdge(node);
		//current = node;
		frontier.erase(frontier.begin() + temp);
		Room* op = node->opposite();
		//current->addEdge(op);
		current = node;
		try {
			// if both node and its opposite are walls
			if (grid2[node->getX()][node->getY()] == nullptr) {
				if (grid2[op->getX()][op->getY()] == nullptr) {

					// open path between the nodes
					grid2[node->getX()][node->getY()] = node;
					grid2[op->getX()][op->getY()] = op;

					// store last node in order to mark it later
					last = op;

					// iterate through direct neighbors of node, same as earlier
					for (int x = -1; x <= 1; x++)
						for (int y = -1; y <= 1; y++) {
							if (x == 0 && y == 0 || x != 0 && y != 0)
								continue;
							try {
								if (grid2[op->getX() + x][op->getY() + y] != nullptr) continue;
							}
							catch (const std::exception& e) {
								continue;
							}
							frontier.push_back(new Room(op->getX() + x, op->getY() + y, op));
						}
				}
			}
		}
		catch (const std::exception& e) { // ignore NullPointer and ArrayIndexOutOfBounds
		}

		// if algorithm has resolved, mark end node
		if (frontier.empty())
			last->setType('E');
			grid2[last->getX()][last->getY()] = last;
	}
	
}

void Map::generateMapOld()
{
	char grid[20][20];

	char s[20];
	for (int i = 0; i < 20; i++)
	{
		//grid[0][i] = new Room();
		s[i] = 'X';

		//const char* grid[10][10];

		for (int x = 0; x < 20; x++)
		{
			grid[x][i] = *s;
			//strcpy(tab2, tmp.c_str());
		}
	}

	// select random point and open as start node
	srand((unsigned)time(0)); // activates the random generator
	startRoom = new Room(rand() % 20, rand() % 20, nullptr);
	grid[startRoom->getX()][startRoom->getY()] = 'S';


	// iterate through direct neighbors of node
	// and activate all the edges of the node
	vector<Room*> frontier;
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
			frontier.push_back(new Room(startRoom->getX() + x, startRoom->getY() + y, startRoom));

		}

	Room* current = startRoom;

	Room* last = nullptr;

	// continue opening up wall sections while node on other side of wall
	// is wall (not explored)
	while (!frontier.empty()) {

		// pick current node at random
		int temp = (int)(rand() % frontier.size());
		Room* node = frontier.at(temp);
		//current->addEdge(node);
		//current = node;
		frontier.erase(frontier.begin() + temp);
		Room* op = node->opposite();
		//current->addEdge(op);
		current = node;
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
							frontier.push_back(new Room(op->getX() + x, op->getY() + y, op));
						}
				}
			}
		}
		catch (const std::exception& e) { // ignore NullPointer and ArrayIndexOutOfBounds
		}

		// if algorithm has resolved, mark end node
		if (frontier.empty())
			grid[last->getX()][last->getY()] = 'E';
	}
}