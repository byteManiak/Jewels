#include "game/board.h"

#include <iostream>
#include <vector>

void Board::update()
{
	if (isKeyPressed(SDL_SCANCODE_Z) || isKeyPressed(SDL_SCANCODE_X))
	{
		isSelecting = !isSelecting;
	}

	if (!isSelecting)
	{
		if (isKeyPressed(SDL_SCANCODE_LEFT)) xCursor--;
		if (isKeyPressed(SDL_SCANCODE_RIGHT)) xCursor++;
		if (isKeyPressed(SDL_SCANCODE_UP)) yCursor--;
		if (isKeyPressed(SDL_SCANCODE_DOWN)) yCursor++;
	}
	else if (!isAnimating)
	{
		if (isKeyPressed(SDL_SCANCODE_LEFT))
		{
			if (xCursor == 0) {}
			else
			{
				swap(xCursor, yCursor, xCursor-1, yCursor, true);
				isSelecting = !isSelecting;
			}
		}
		else if (isKeyPressed(SDL_SCANCODE_RIGHT))
		{
			if (xCursor == 7) {}
			else
			{
				swap(xCursor, yCursor, xCursor+1, yCursor, true);
				isSelecting = !isSelecting;
			}
		}
		else if (isKeyPressed(SDL_SCANCODE_UP))
		{
			if (yCursor == 0) {}
			else
			{
				swap(xCursor, yCursor, xCursor, yCursor-1, true);
				isSelecting = !isSelecting;
			}
		}
		else if (isKeyPressed(SDL_SCANCODE_DOWN))
		{
			if (yCursor == 7) {}
			else
			{
				swap(xCursor, yCursor, xCursor, yCursor+1, true);
				isSelecting = !isSelecting;
			}
		}
	}

	if (xCursor < 0) xCursor = 0;
	else if (xCursor > 7) xCursor = 7;

	if (yCursor < 0) yCursor = 0;
	else if (yCursor > 7) yCursor = 7;

	bool anyGemMoving = false;

	for(int i = 0; i < 8; i++)
	for(int j = 0; j < 8; j++)
	{
		if (i == xCursor && j == yCursor)
		{
			drawRectangle(BASEX+i*16, BASEY+j*16, 17, 17, 2, true);
			if(gems[i][j])
			{
				gems[i][j]->draw(true);
				if (gems[i][j]->isMoving) anyGemMoving = true;
			}
		}
		else
		{
			drawRectangle(BASEX+i*16, BASEY+j*16, 17, 17, 2);
			if (gems[i][j])
			{
				gems[i][j]->draw();
				if (gems[i][j]->isMoving) anyGemMoving = true;
			}
		}
	}

	isAnimating = anyGemMoving;

	if (!isAnimating)
	{
		findMatch(false);
		if (hasMatch) sweepMatches();

		if (swapState == SWAP_FIRST)
		{
			if (hasMatch) swapState = NO_SWAP;
			else swap(x1swap, y1swap, x2swap, y2swap, true);
		}
		else if (swapState == SWAP_BACK) swapState = NO_SWAP;
	}
}

enum Dir
{
	LEFT, RIGHT,
	UP, DOWN
};

bool Board::isSlotAvailable(int x, int y)
{
	if (x < 0 || x > 7 || y < 0 || y > 7) return false;

	return gems[x][y] == nullptr;
}

void Board::genPartialMatch(int x, int y, int type)
{
	// Don't generate a partial match where there is already a gem
	if (gems[x][y]) return genPartialMatch(rand()%8, rand()%8, type);

	// Establish which way to generate the match
	Dir dir = (Dir)(rand()%4);
	if (dir == DOWN && y >= 6) dir = UP;
	else if (dir == UP && y <= 1) dir = DOWN;
	else if (dir == RIGHT && x >= 6) dir = LEFT;
	else if (dir == LEFT && x <= 1) dir = RIGHT;

	// Generate match in the given direction

	int x1, y1, x2, y2;
	switch(dir)
	{
		case LEFT:
		case RIGHT:
		{
			x1 = x+1; x2 = x+2;
			if (dir == LEFT) {x1-=2; x2-=4;}

			int r = rand()%6;
			switch(r)
			{
				case 0:
					y1 = y+1; y2 = y;
					break;
				case 1:
					y1 = y-1; y2 = y;
					break;
				case 2:
					y1 = y; y2 = y-1;
					break;
				case 3:
					y1 = y; y2 = y+1;
					break;
				case 4:
					y1 = y-1; y2 = y-1;
					break;
				case 5:
					y1 = y+1; y2 = y+1;
					break;
				default:
					break;
			}
			break;
		}
		case UP:
		case DOWN:
		{
			y1 = y+1; y2 = y+2;
			if (dir == UP) {y1-=2; y2-=4;}

			int r = rand()%6;
			switch(r)
			{
				case 0:
					x1 = x+1; x2 = x;
					break;
				case 1:
					x1 = x-1; x2 = x;
					break;
				case 2:
					x1 = x; x2 = x-1;
					break;
				case 3:
					x1 = x; x2 = x+1;
					break;
				case 4:
					x1 = x-1; x2 = x-1;
					break;
				case 5:
					x1 = x+1; x2 = x+1;
					break;
				default:
					break;
			}
			break;
		}
	}

	if (isSlotAvailable(x1,y1) && isSlotAvailable(x2,y2))
	{
		gems[x][y] = new Gem(type, x, y);
		gems[x1][y1] = new Gem(type, x1, y1);
		gems[x2][y2] = new Gem(type, x2, y2);
	}
	else return genPartialMatch(rand()%8, rand()%8, type);
}

void Board::avoidMatches()
{
	findMatch(true);

	for(int i = 1; i <= 6; i++)
	for(int j = 0; j < 8; j++)
		if (gems[i-1][j]->type == gems[i][j]->type && gems[i][j]->type == gems[i+1][j]->type)
			gems[i][j]->setNextType();


	for(int j = 1; j <= 6; j++)
	for(int i = 0; i < 8; i++)
		if (gems[i][j-1]->type == gems[i][j]->type && gems[i][j]->type == gems[i][j+1]->type)
			gems[i][j]->setNextType();
}

void Board::genBoard()
{
	// A partial match is a pattern where a match is possible when making a single move
	// e.g. below a match is possible by swapping Y and the X under it
	// X X Y
	// T Z X

	// Gen partial matches

	// Clear the board
	for (int i = 0; i < 8; i++)
	for (int j = 0; j < 8; j++)
		gems[i][j] = nullptr;

	// Gen one match for each color
	for(int i = 0; i < 6; i++)
	{
		genPartialMatch(rand()%8, rand()%8, i+1);
	}

	// Gen random gems for the rest of the board
	for(int i = 0; i < 8; i++)
	for(int j = 0; j < 8; j++)
		if (!gems[i][j]) gems[i][j] = new Gem(rand()%6+1, i, j);

	avoidMatches();
	while(hasMatch)	avoidMatches();
}

void Board::findMatch(bool initBoardStage)
{
	hasMatch = false;

	for(int i = 0; i < 6; i++)
	for(int j = 0; j < 8; j++)
	{
		if (gems[i][j]->type == gems[i+1][j]->type && gems[i][j]->type == gems[i+2][j]->type)
		{
			if (!initBoardStage)
			{
				gems[i][j]->isMatched = true;
				gems[i+1][j]->isMatched = true;
				gems[i+2][j]->isMatched = true;
			}
			hasMatch = true;
		}
	}

	for(int i = 0; i < 8; i++)
	for(int j = 0; j < 6; j++)
	{
		if (gems[i][j]->type == gems[i][j+1]->type && gems[i][j]->type == gems[i][j+2]->type)
		{
			if (!initBoardStage)
			{
				gems[i][j]->isMatched = true;
				gems[i][j+1]->isMatched = true;
				gems[i][j+2]->isMatched = true;
			}
			hasMatch = true;
		}
	}
}

void Board::sweepMatches()
{
	for(int i = 0; i < 8; i++)
	for(int j = 0; j < 8; j++)
	{
		if (gems[i][j]->isMatched)
		{
			delete(gems[i][j]);
			gems[i][j] = nullptr;
			for (int k = j; k > 0; k--)
				swap(i, k, i, k-1, false);
			gems[i][0] = new Gem(rand()%6+1, i, 0);
		}
	}
}

void Board::swap(int x1, int y1, int x2, int y2, bool moveCursor)
{
	std::swap(gems[x1][y1], gems[x2][y2]);

	if (moveCursor)
	{
		xCursor = x2; yCursor = y2;
	}

	if (gems[x1][y1]) gems[x1][y1]->setCoords(x1, y1);
	if (gems[x2][y2]) gems[x2][y2]->setCoords(x2, y2);

	x1swap = x2; y1swap = y2;
	x2swap = x1; y2swap = y1;

	if (swapState == NO_SWAP) swapState = SWAP_FIRST;
	else if (swapState == SWAP_FIRST) swapState = SWAP_BACK;
}