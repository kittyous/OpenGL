// Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <MGLE.h>
#include <SFML/System.hpp>
#include "SolarSys.h"

Game* game;

int main(int argc, char** argv)
{
	
	std::cout << argv << std::endl;
	glutInit(&argc,argv);
	game = new Game();
	Sys* sys = new Sys(game);
	while (game->graphics->window->Open()) {
		sf::sleep(sf::microseconds(16667));
		
		game->Update();
		sys->Run();
		game->graphics->window->Display();
		game->graphics->window->PollEvents();
	}
	return 0;
}


