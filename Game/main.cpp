// Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <MGLE.h>

Game* game;
int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	game = new Game();
	
	return 0;
}

