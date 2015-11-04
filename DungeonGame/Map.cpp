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

				(grid2[i][j]->getEdge("west")) ? cout << "-" : cout << " "; 
				cout << grid2[i][j]->getType();
				(grid2[i][j]->getEdge("east")) ? cout << "-" : cout << " ";
			}
			else
				cout << " X ";
		}
		cout << endl;
		for (int j = 0; j <= max_X; j++) {
			if (grid2[i][j] != nullptr){
				
				(grid2[i][j]->getEdge("south")) ? cout << "|" : cout << " ";
				(grid2[i][j]->getEdge("north")) ? cout << "|" : cout << " ";
			}
			else
				cout << " ";
		}
		cout << endl;
	}
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

void Map::randomPaths()
{
	for (int i = 0; i <= max_Y; i++)
	{
		for (int x = 0; x <= max_X; x++)
		{
			Room* temp = new Room(x, i, nullptr);
			temp->setType('N');

			grid2[i][x] = temp;
		}
	}

	// select random point and open as start node
	srand((unsigned)time(0)); // activates the random generator
	grid2[rand() % max_Y][rand() % max_X]->setType('S');


	// select random point and open as start node
	//srand((unsigned)time(0)); // activates the random generator
	grid2[rand() % max_Y][rand() % max_X]->setType('E');


	for (int i = 0; i <= max_Y; i++)
	{
		for (int x = 0; x <= max_X; x++)
		{
			vector<string> paths = { "north", "east", "south", "west" };

			string randPath = paths[rand() % 3];

			if (randPath == "north")
			{
				if(i > 0 && i < max_Y)
					grid2[i][x]->addEdge(randPath, grid2[i-1][x]);
			}
			if (randPath == "east")
			{
				if (x > 0 && x < max_X)
					grid2[i][x]->addEdge(randPath, grid2[i][x+1]);
			}
			if (randPath == "south")
			{
				if (i > 0 && i < max_Y)
					grid2[i][x]->addEdge(randPath, grid2[i + 1][x]);
			}
			if (randPath == "west")
			{
				if (x > 0 && x < max_X)
					grid2[i][x]->addEdge(randPath, grid2[i][x - 1]);
			}

			//grid2[i][x]->addEdge(paths[rand() % 3]);

		}
	}

}


void Map::generateMap()
{

	for (int i = 0; i <= max_Y; i++)
	{

		//const char* grid[10][10];

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
	grid2[startRoom->getY()][startRoom->getX()] = startRoom;


	// iterate through direct neighbors of node
	// and activate all the edges of the node
	vector<Room*> frontier;
	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {
			if (x == 0 && y == 0 || x != 0 && y != 0)
				continue;

			if (startRoom->getY() > 0 && startRoom->getY() < max_Y && startRoom->getX() > 0 && startRoom->getX() < max_X && grid2[startRoom->getY() + x][startRoom->getX() + y]->getType() != 'X')
				continue;

			// add eligible points to edges

			/*
			Room* temp = new Room(startRoom->getX() + y, startRoom->getY() + x, startRoom);

			if (temp->getY() == startRoom->getY() - 1)
				startRoom->addEdge("north", temp);
			if (temp->getX() == startRoom->getX() + 1)
				startRoom->addEdge("east", temp);
			if (temp->getY() == startRoom->getY() + 1)
				startRoom->addEdge("south", temp);
			if (temp->getX() == startRoom->getX() - 1)
				startRoom->addEdge("west", temp);
			*/

			frontier.push_back(new Room(startRoom->getX() + y, startRoom->getY() + x, startRoom));

		}
	}

	//Room* current = startRoom;

	Room* last = nullptr;


	// continue opening up wall sections while node on other side of wall
	// is wall (not explored)
	while (!frontier.empty()) {

		// pick current node at random
		//srand((unsigned)time(0)); // activates the random generator
		int temp = (int)(rand() % frontier.size());
		Room* current = frontier.at(temp);
		Room* op = current->opposite();

		int tempX = current->getX();
		int tempY = current->getY();
		//current->addEdge(node);

		int tempX2 = op->getX();
		int tempY2 = op->getY();
		//current = node;
		frontier.erase(frontier.begin() + temp);
		//Room* op = current->opposite();
		//current->addEdge(op);
		//current = node;
			// if both node and its opposite are walls
			if ( tempY > 0 && tempY < max_Y && tempX > 0 && tempX < max_X && grid2[tempY][tempX]->getType() == 'X') {
				if (tempY2 > 0 && tempY2 < max_Y && tempX2 > 0 && tempX2 < max_X && grid2[tempY2][tempX2]->getType() == 'X') {

					// open path between the nodes
					
					
					if (op->getY() == current->getY() - 1)
						current->addEdge("north", op);
					if (op->getX() == current->getX() + 1)
						current->addEdge("east", op);
					if (op->getY() == current->getY() + 1)
						current->addEdge("south", op);
					if (op->getX() == current->getX() - 1)
						current->addEdge("west", op);
						
					grid2[tempY][tempX] = current;
					grid2[tempY][tempX]->setType('N');

					
					if (current->getY() == op->getY() - 1)
						op->addEdge("north", current);
					if (current->getX() == op->getX() + 1)
						op->addEdge("east", current);
					if (current->getY() == op->getY() + 1)
						op->addEdge("south", current);
					if (current->getX() == op->getX() - 1)
						op->addEdge("west", current);
						
					grid2[tempY2][tempX2] = op;
					grid2[tempY2][tempX2]->setType('N');

					// store last node in order to mark it later
					last = op;

					// iterate through direct neighbors of node, same as earlier
					for (int x = -1; x <= 1; x++)
						for (int y = -1; y <= 1; y++) {
							if (x == 0 && y == 0 || x != 0 && y != 0)
								continue;

							if (tempY2+x > 0 && tempY2+x < max_Y && tempX2+y > 0 && tempX2+y < max_X && grid2[tempY2 + x][tempX2 + y]->getType() != 'X') {
								continue;
							}
							
							// add eligible points to edges

							
							Room* temp = new Room(op->getX() + y, op->getY() + x, op);

							if (temp->getY() == startRoom->getY() - 1)
								startRoom->addEdge("north", temp);
							if (temp->getX() == startRoom->getX() + 1)
								startRoom->addEdge("east", temp);
							if (temp->getY() == startRoom->getY() + 1)
								startRoom->addEdge("south", temp);
							if (temp->getX() == startRoom->getX() - 1)
								startRoom->addEdge("west", temp);
								

							frontier.push_back(new Room(tempX2 + y,tempY2 + x, op));
						}
				}
			}


		// if algorithm has resolved, mark end node
		if (frontier.empty()) {
			//last->setType('E');
			grid2[tempY2][tempX2]->setType('E');
		}
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