#pragma once
#include "Game.h"
#include <string>

class InputHandler
{
public:
	static InputHandler& getInstance()
	{
		/* The only instance, guaranteed to be lazy initialized,
		guaranteed that it will be destroyed correctly */
		static InputHandler instance;
		return instance;
	}

	bool handleInput();
	string getOptions();
	string moveDirections();
private:
	// Private constructor
	InputHandler() {};

	// Stop the compiler generating methods of copy the object
	InputHandler(InputHandler const&) = delete;
	void operator=(InputHandler const&) = delete;

	void move();
	void block();
	bool fighting;

	std::string input;
};

