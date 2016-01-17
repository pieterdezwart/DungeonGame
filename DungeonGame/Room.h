#pragma once
#include <string>
#include <map>
#include <iostream>
#include <vector>

using namespace std;

class Map;
class Enemy;
class Trap;

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
	map<string, Room*> getEdges() { return edges; };
	bool isLinked(Room* r);
	int numEdges();
	string randFreeEdge();
	bool isExplored() { return explored; };
	void setExplored(bool exp) { explored = exp; };
	Map* getMap() { return map; };

	vector<Enemy*> getEnemies();
	vector<Trap*> getTraps();
private:
	bool explored = false;
	int x, y = 0;

	map<string, Room*> edges;

	string size;
	string state;
	string furniture;
	string light;

	char type = 'N';

	int distance; // BFS property

	string description = "x";
	Map* map;
};

