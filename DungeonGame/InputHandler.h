#pragma once
#include "Game.h"
#include <string>
#include <algorithm>

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
	void inventory();

	std::string input;

	bool is_number(std::string in) {
		return !in.empty() && std::find_if(in.begin(),
			in.end(), [](char c) { return !isdigit(c); }) == in.end();
	};
};

