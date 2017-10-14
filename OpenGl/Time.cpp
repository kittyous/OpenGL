#include "stdafx.h"
#include "Time.h"
#include <SDL.h>

Uint32 startTime;
void Time::SetStartTicks()
{
	startTime = SDL_GetTicks();
}
float Time::deltaTMP = 0;
float Time::deltaReturn = 0;
float Time::deltaTime;
void Time::setDeltaTime() {
	deltaReturn =   SDL_GetTicks() - deltaTMP;
	deltaTMP = SDL_GetTicks();
	deltaTime =  deltaReturn/1000;
}
Uint32 Time::GetTicks() {
	return SDL_GetTicks() - startTime;
}
