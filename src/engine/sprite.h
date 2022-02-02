#pragma once

#include <string>

class Sprite
{
public:
	/**
	 * @param texture Internal name of the spritesheet's texture.
	 * @param tileW Width of a tile from the sprite sheet.
	 * @param tileH Height of a tile from the sprite sheet.
	 * @param numTiles Number of tiles making up the entire sprite sheet.
	 * @param tickSpeed How fast the sprite's current tile changes.
	 */
	Sprite(std::string texture, int tileW, int tileH, int numTiles, int tickSpeed);

	/**
	 * @brief Draw a tile from the sprite sheet.
	 */
	void drawTile(int x, int y, int tile = -1);
	/**
	 * @brief Draw the sprite's currently selected tile.
	 */
	void draw(int x, int y);
	void setSprite(std::string texture);

private:
	int tickSpeed;
	int startTick;

	int numTiles;
	int currentTile = 0;

	int tileW, tileH;
	std::string texture;
};