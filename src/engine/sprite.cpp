#include "engine/sprite.h"

#include "engine/texture.h"
#include <SDL2/SDL.h>
#include <iostream>

Sprite::Sprite(std::string texture, int tileW, int tileH, int numTiles, int tickSpeed)
{
	this->texture = texture;
	this->tileW = tileW;
	this->tileH = tileH;
	this->numTiles = numTiles;
	this->tickSpeed = tickSpeed;

	startTick = SDL_GetTicks();
}

void Sprite::drawTile(int x, int y, int tile)
{
	if (tile == -1) drawTexture(texture, x, y, tileW, tileH, currentTile*tileW, 0, tileW, tileH);
	else drawTexture(texture, x, y, tileW, tileH, tile*tileW, 0, tileW, tileH);
}

void Sprite::draw(int x, int y)
{
	if (SDL_GetTicks() - startTick > tickSpeed)
	{
		startTick = SDL_GetTicks();
		currentTile = (currentTile+1) % numTiles;
	}

	drawTexture(texture, x, y, tileW, tileH, tileW*currentTile, 0, tileW, tileH);
}