#pragma once
#include <string>
#include <map>
#include <iostream>

using namespace std;

class Map;

class Room
{
public:
	Room(int x, int y, Map* m);
	~Room();

	string getDescription();
	void setDescription(string desc);

	int getX() { return x; };
	int getY() { return y; };


	void addEdge(string dir, Room* edge);
	void addEdge(Room* edge);

	Room* getEdge(string dir);

	void setType(char c);

	char getType() {
		return type;
	};

	string getExitStrings();

	bool isLinked(Room* r);
	int numEdges();
	string randFreeEdge();

private:
	int x, y = 0;

	map<string, Room*> edges;

	string size;
	string state;
	string furniture;
	string light;

	char type = 'N';

	int distance; // BFS property

	string description = "x";
};

