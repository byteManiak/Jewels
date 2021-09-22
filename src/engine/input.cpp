#include "engine/input.h"

static const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
static Uint8 prevState[SDL_NUM_SCANCODES];

void updateKeyboard()
{
	memcpy(prevState, keyboardState, sizeof(Uint8)*SDL_NUM_SCANCODES);
}

bool isKeyPressed(SDL_Scancode scancode)
{
	return keyboardState[scancode] && !prevState[scancode];
}

bool isKeyDown(SDL_Scancode scancode)
{
	return keyboardState[scancode] && prevState[scancode];
}

bool isKeyReleased(SDL_Scancode scancode)
{
	return prevState[scancode] && !keyboardState[scancode];
}