#include "engine/text.h"

#include <SDL2/SDL_ttf.h>

#include <iostream>

static TTF_Font *font;
static int fontW, fontH;

void loadFont()
{
	TTF_Init();
	font = TTF_OpenFont("assets/font.ttf", 8);
	TTF_SizeText(font, "s", &fontW, &fontH);
}

void drawText(std::string text, int x, int y)
{
	SDL_Rect r = {x, y, text.length()*fontW, fontH};

	SDL_Surface *s = TTF_RenderText_Solid(font, text.c_str(), currentPalette->colors[3]);
	SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, s);
	SDL_RenderCopy(renderer, t, NULL, &r);
	SDL_DestroyTexture(t);
	SDL_FreeSurface(s);
}
