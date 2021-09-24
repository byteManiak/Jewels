#pragma once

#include "engine/engine.h"

class Gem
{
public:
	Gem(int type, int x, int y);
	~Gem();
	void draw(bool isSelected = false);
	void setNextType();
	void setVisible(bool isVisible);
	void setCoords(int x, int y);

	int type = 0;
	bool isSelected = false;
	bool isMoving = false;

private:
	int xdest, ydest;
	float x, y;
	Sprite *sprite = NULL;

	int startTick;
};