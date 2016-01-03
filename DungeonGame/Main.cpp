#pragma once
#include "Game.h"

int main(int argc, char* args[]) {

	//Dungeon* dungeon = new Dungeon();

	//Game* game = new Game();

	Game::getInstance().init();

	Game::getInstance().gameLoop();

	//cout << "test";

	return 0;
}