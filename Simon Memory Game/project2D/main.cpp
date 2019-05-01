//----------------------------------------------------------------------------
// This is the entry-point for your game.
// Creates and runs the Game2D class which contains the game loop.
//----------------------------------------------------------------------------
#include <crtdbg.h>
//For the time function
#include <time.h>
//For the sleep function
#include <windows.h>
#include "Game2D.h"

int main() 
{
	//Check for memeory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//Seed the randome number generator
	srand((unsigned int)time(0));

	//Create the Application
	Game2D* game = new Game2D("AIE", 440, 470, false);

	//Run the game loop
	game->Run();

	//Clean up
	delete game;

	return 0;
}