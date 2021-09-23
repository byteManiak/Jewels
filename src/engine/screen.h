#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

extern SDL_Renderer *renderer;

/**
 * @brief Initialize the game screen.
 * 
 * @param title Name of the game window.
 * @param xRes X resolution.
 * @param yRes Y resolution.
 * @param intScaling Enable integer scaling of resolution (default=true).
 */
void initScreen(const char *title, int xRes, int yRes, bool intScaling = true);

void deinitScreen();

void beginDraw();
void endDraw();
void draw();

void drawRectangle(int x, int y, int w, int h, int color, bool fill = false);