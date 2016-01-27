#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW
#include <stdlib.h>
#include <crtdbg.h>
//#define DEBUG_NEW new(_NORMAL_BLOCK ,__FILE__, __LINE__)
#define DEBUG_NEW   new( _CLIENT_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include "Game.h"

int main(int argc, char* args[]) {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

	srand((unsigned)time(0)); // activates the random generator

	Game::getInstance().init();

	Game::getInstance().gameLoop();

	//_CrtDumpMemoryLeaks();

	return 0;
}