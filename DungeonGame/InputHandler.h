#pragma once
#include "Game.h"
#include <string>

class InputHandler
{
public:
	static void handleInput(string input);
	static string getOptions();
	static string moveDirections();
private:
	static void move();
};

