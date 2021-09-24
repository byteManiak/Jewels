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
	bool isSlotAvailable(int x, int y);
	void genPartialMatch(int x, int y, int type);
	void avoidMatches();
	void genBoard();

	void swap(int x1, int y1, int x2, int y2);

	bool isSelecting = false;
	int xCursor = 4, yCursor = 4;
	Gem *gems[8][8];
};