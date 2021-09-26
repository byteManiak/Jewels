#include "engine/screen.h"
#include "engine/texture.h"
#include "engine/color.h"
#include <iostream>
#include <unordered_map>

static SDL_Window *window;
SDL_Renderer *renderer;
static SDL_Texture *renderTarget;

void initScreen(const char *title, int xRes, int yRes, bool intScaling)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	// Create game window with triple-size pixels
	// Engine assumes the resolution will be low enough
	// to fit this tripled resolution on screen
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							  xRes*3, yRes*3, SDL_WINDOW_RESIZABLE);

	// Create game renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	// Optionally enable integer scaling (on by default)
	if (intScaling)
	{
		SDL_RenderSetIntegerScale(renderer, SDL_TRUE);
		SDL_RenderSetLogicalSize(renderer, xRes, yRes);
	}

	// Set a render target into which we can draw with the desired resolution
	renderTarget = SDL_CreateTexture(renderer,
									 SDL_PIXELFORMAT_RGBA8888,
									 SDL_TEXTUREACCESS_TARGET,
									 xRes, yRes);

	addColorPalette("Default", 0x050500, 0x033822, 0x3e9533, 0xd4f044);
	setColorPalette("Default", true);
}

void deinitScreen()
{
	SDL_DestroyTexture(renderTarget);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void beginDraw()
{
	updatePalette();

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	// Clear the screen contents
	SDL_RenderClear(renderer);

	// Draw to the render target that has the screen resolution we set
	SDL_SetRenderTarget(renderer, renderTarget);
	SDL_SetRenderDrawColor(renderer,
						   currentPalette->colors[2].r,
						   currentPalette->colors[2].g,
						   currentPalette->colors[2].b,
						   0);
	// Clear the render target contents
	SDL_RenderClear(renderer);
	SDL_RenderDrawRect(renderer, NULL);
}

void endDraw()
{
	// Draw render target to the screen
	SDL_SetRenderTarget(renderer, NULL);
	SDL_RenderCopy(renderer, renderTarget, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void drawRectangle(int x, int y, int w, int h, int color, bool fill)
{
	SDL_Rect r = {x, y, w, h};
	SDL_SetRenderDrawColor(renderer,
						   currentPalette->colors[color].r,
						   currentPalette->colors[color].g,
						   currentPalette->colors[color].b,
						   0);
	if (fill) SDL_RenderFillRect(renderer, &r);
	else
	{
		SDL_RenderDrawLine(renderer, x, y, x, y+h);
		SDL_RenderDrawLine(renderer, x, y, x+w, y);
		SDL_RenderDrawLine(renderer, x, y+h, x+w, y+h);
		SDL_RenderDrawLine(renderer, x+w, y, x+w, y+h);
	}
}
