#pragma once

#include <SDL2/SDL.h>

void initInput();

#define LEFT_CLICK 1
#define MIDDLE_CLICK 2
#define RIGHT_CLICK 3

std::pair<int,int> getMouseCoords();
bool isMouseButtonPressed(int button);

void updateKeyboard();
bool isKeyPressed(SDL_Scancode scancode);
bool isKeyDown(SDL_Scancode scancode);
bool isKeyReleased(SDL_Scancode scancode);