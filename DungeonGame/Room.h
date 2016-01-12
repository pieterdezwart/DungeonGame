#pragma once
#include <string>
#include <map>
#include <iostream>

using namespace std;

class Room
{
public:
	Room(int x, int y, Room* r);
	~Room();

	string getDescription();
	void setDescription(string desc);

	int getX() { return x; };
	int getY() { return y; };

	Room* opposite();

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
	bool isExplored() { return explored; };
	void setExplored(bool exp) { explored = exp; };
private:
	bool explored = false;
	int x, y = 0;

	Room* parent = nullptr;

	map<string, Room*> edges;

	string size;
	string state;
	string furniture;
	string light;

	char type = 'N';

	int distance; // BFS property

	string description = "x";
};

