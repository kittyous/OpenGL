// Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <MGLE.h>
#include <SFML/System.hpp>
#include "SolarSys.h"
#include <windows.h>
Game* game;
using namespace MGLE;
	int main(int argc, char** argv)
	{
		glutInit(&argc, argv);
		game = new Game();
		Sys sys(game);
		while (game->graphics->window->Open()) {
			sf::sleep(sf::microseconds(16667));
			sys.Run();
			game->Update();
			game->graphics->window->Display();
			game->graphics->window->PollEvents();
		}
		
		return 0;
	}



