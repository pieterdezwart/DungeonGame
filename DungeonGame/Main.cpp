#pragma once
#include "Game.h"

int main(int argc, char* args[]) {

	srand((unsigned)time(0)); // activates the random generator

	Game::getInstance().init();

	Game::getInstance().gameLoop();

	return 0;
}