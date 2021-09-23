#pragma once

#include "engine/engine.h"

class Gem
{
public:
	Gem(int type);
	~Gem();
	void draw(int x, int y);

	int type;
	bool isSelected = false;

private:
	Sprite *sprite;
};