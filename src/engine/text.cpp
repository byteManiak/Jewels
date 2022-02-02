#include "engine/text.h"

#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <unordered_map>

std::unordered_map<std::string, TTF_Font*> fonts;

static TTF_Font *currentFont;

void initTTF()
{
	TTF_Init();
}

void createFont(std::string path, int fontSize, std::string name)
{
	if (fonts.find(name) != fonts.end())
	{
		std::cout << "Font \"" << name << "\" is already loaded in memory" << std::endl;
		return;
	}

	TTF_Font *font = TTF_OpenFont(path.c_str(), fontSize);
	fonts[name] = font;
}

void setFont(std::string name)
{
	currentFont = fonts[name];
}

void drawText(std::string text, int x, int y)
{
	SDL_Surface *s = TTF_RenderText_Solid(currentFont, text.c_str(), currentPalette->colors[3]);
	SDL_Rect r = {x, y, s->w, s->h};
	SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, s);
	SDL_RenderCopy(renderer, t, NULL, &r);
	SDL_DestroyTexture(t);
	SDL_FreeSurface(s);
}
