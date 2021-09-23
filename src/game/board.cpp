#include "game/board.h"

#include <iostream>

#define BASEX 30
#define BASEY 1

Board::Board()
{
	// Gen random gems
	for(int i = 0; i < 8; i++)
	for(int j = 0; j < 8; j++)
	{
		int newGem = rand()%6+1;
		if (j >= 2)
		{
			while (newGem == gems[i][j-1]->type && newGem == gems[i][j-2]->type)
			{
				newGem = rand()%6+1;
			}
		}
		gems[i][j] = new Gem(newGem);
	}

	// Scramble a bit if there are matches
	for(int i = 0; i < 8; i++)
	{
		int streak = 0;
		for(int j = 0; j < 7; j++)
		{
			if (gems[i][j]->type == gems[i][j+1]->type) streak++;

			// Swap in a random direction
			if (streak == 2)
			{
				if (j > 0 && gems[i][j-1]->type != gems[i][j]->type)
					std::swap(gems[i][j], gems[i][j-1]);
				else if (i > 0)
					std::swap(gems[i][j], gems[i-1][j]);
				else
					std::swap(gems[i][j], gems[i+1][j]);
			}
		}
	}
}

void Board::update()
{
	for(int i = 0; i < 8; i++)
	for(int j = 0; j < 8; j++)
	{
		drawRectangle(BASEX+i*16, BASEY+j*16, 17, 17, 2);
		gems[i][j]->draw(BASEX+1+i*16, BASEY+1+j*16);
	}
}
