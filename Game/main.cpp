// Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <MGLE.h>
#include <SFML/System.hpp>

Game* game;
int main(int argc, char** argv)
{
	std::cout << argv << std::endl;
	glutInit(&argc,argv);
	game = new Game();
	
	while (game->graphics->window->Open()) {
		sf::sleep(sf::microseconds(16667));
		game->Update();
		game->graphics->window->PollEvents();
	}
	return 0;
}


