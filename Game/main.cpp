// Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SDL.h>
#include "Audio.cpp"
#include "Game.cpp"
#include "Graphics.cpp"
#include "Input.cpp"
#include "Time.cpp"
#include "Vector3.cpp"
Game* game;
int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	game = new Game();
	SDL_Quit();
	
	return 0;
}

