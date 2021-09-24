#pragma once

#include "engine/engine.h"

class Gem
{
public:
	Gem(int type);
	~Gem();
	void draw(int x, int y, bool isSelected = false);
	void setNextType();
	void setVisible(bool isVisible);

	int type = 0;
	bool isSelected = false;
	bool isSwapping = false;

private:
	Sprite *sprite = NULL;
};