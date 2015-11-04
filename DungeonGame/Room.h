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

	Room* getEdge(string dir);

	void setType(char c);

	char getType() {
		return type;
	};

private:
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

