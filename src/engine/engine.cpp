#include "engine/engine.h"

void updateEvents()
{
	updateKeyboard();
	SDL_PumpEvents();
}