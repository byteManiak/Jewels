#pragma once

#include <SDL2/SDL.h>

void initInput();

#define LEFT_CLICK   1 << 0
#define MIDDLE_CLICK 1 << 1
#define RIGHT_CLICK  1 << 2

/**
 * @brief Get the mouse coordinates relative to the renderer viewport.
 */
std::pair<int,int> getMouseCoords();

/**
 * @brief Check if one or more mouse buttons are pressed.
 * @param button Bitmask of buttons to check.
 */
bool isMouseButtonPressed(int button);

/**
 * @brief Update the keyboard state.
 */
void updateKeyboard();

/**
 * @brief Check if a key has just been pressed.
 * @param scancode Key to check.
 */
bool isKeyPressed(SDL_Scancode scancode);

/**
 * @brief Check if a key is being held pressed.
 * @param scancode Key to check.
 */

bool isKeyDown(SDL_Scancode scancode);

/**
 * @brief Check if a key has just been released.
 * @param scancode Key to check.
 */
bool isKeyReleased(SDL_Scancode scancode);