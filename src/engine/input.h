#pragma once

#include <SDL2/SDL.h>

void updateKeyboard();
bool isKeyPressed(SDL_Scancode scancode);
bool isKeyDown(SDL_Scancode scancode);
bool isKeyReleased(SDL_Scancode scancode);