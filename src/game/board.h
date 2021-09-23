#pragma once

#include "engine/engine.h"

#include "game/common.h"
#include "game/gem.h"

class Board
{
public:
	Board();
	void update();

private:
	Gem *gems[8][8];
	int baseX, baseY;
};