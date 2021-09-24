#include "engine/engine.h"

void updateEvents()
{
	updateKeyboard();
	SDL_PumpEvents();
	SDL_Delay(10);
}