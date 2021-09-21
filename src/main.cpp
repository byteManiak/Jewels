#include "engine/engine.h"
#include <iostream>

#define XRES 160
#define YRES 144

int main(int argc, char **argv)
{
	initScreen("Jewels!", XRES, YRES);

	createTexture("assets/jewel1.pcx", "gem1");
	createTexture("assets/jewel2.pcx", "gem2");
	createTexture("assets/logo.pcx", "logo");

	setColorPalette("Meadow");
	SDL_Event ev;
	while(true)
	{
		bool quit = false;

		SDL_PumpEvents();

		static int xpos = 0, ypos = 0;

		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_KEYDOWN)
			{
				if (ev.key.keysym.sym == SDLK_ESCAPE)
					quit = true;
				if (ev.key.keysym.sym == SDLK_SPACE)
					setNextColorPalette();

				if (ev.key.keysym.sym == SDLK_RIGHT)
					xpos = (xpos < 7) ? xpos+1 : xpos;
				if (ev.key.keysym.sym == SDLK_LEFT)
					xpos = (xpos > 0) ? xpos-1 : xpos;
				if (ev.key.keysym.sym == SDLK_UP)
					ypos = (ypos > 0) ? ypos-1 : ypos;
				if (ev.key.keysym.sym == SDLK_DOWN)
					ypos = (ypos < 7) ? ypos+1 : ypos;
			}
		}

		beginDraw();

		SDL_Rect t = {29+xpos*16, 3+ypos*16, 15, 15};
		SDL_SetRenderDrawColor(renderer,
							   currentPalette->colors[2].r,
							   currentPalette->colors[2].g,
							   currentPalette->colors[2].b,
							   0);
		SDL_RenderFillRect(renderer, &t);

		for(int i = 0; i < 9; i++)
		{
			SDL_RenderDrawLine(renderer, 28, 2+i*16, 28+16*8, 2+i*16);
			SDL_RenderDrawLine(renderer, 28+i*16, 2, 28+i*16, 2+16*8);
		}
		for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
		{
			if (xpos == i && ypos == j)
				drawTexture((i+j)%2==0?"gem1":"gem2", 29+i*16, 3+j*16, 15, 15, 15*((SDL_GetTicks()/85)%6), 0, 15 ,15);
			else
				drawTexture((i+j)%2==0?"gem1":"gem2", 29+i*16, 3+j*16, 15, 15, 0, 0, 15 ,15);
		}

		endDraw();

		if (quit) break;
	}

	deleteTexture("gem1");

	return 0;
}