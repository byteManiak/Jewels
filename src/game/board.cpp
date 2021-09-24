#include "game/board.h"

#include <iostream>
#include <vector>

#define BASEX 30
#define BASEY 1

Board::Board()
{
	genBoard();
}

void Board::update()
{
	if (!isSelecting)
	{
		if (isKeyPressed(SDL_SCANCODE_LEFT)) xCursor--;
		if (isKeyPressed(SDL_SCANCODE_RIGHT)) xCursor++;
		if (isKeyPressed(SDL_SCANCODE_UP)) yCursor--;
		if (isKeyPressed(SDL_SCANCODE_DOWN)) yCursor++;
	}
	else
	{
		if (isKeyPressed(SDL_SCANCODE_LEFT))
		{
			if (xCursor == 0) {}
			else
			{
				swap(xCursor, yCursor, xCursor-1, yCursor);
				isSelecting = !isSelecting;
			}
		}
		if (isKeyPressed(SDL_SCANCODE_RIGHT))
		{
			if (xCursor == 7) {}
			else
			{
				swap(xCursor, yCursor, xCursor+1, yCursor);
				isSelecting = !isSelecting;
			}
		}
		if (isKeyPressed(SDL_SCANCODE_UP))
		{
			if (yCursor == 0) {}
			else
			{
				swap(xCursor, yCursor, xCursor, yCursor-1);
				isSelecting = !isSelecting;
			}
		}
		if (isKeyPressed(SDL_SCANCODE_DOWN))
		{
			if (yCursor == 7) {}
			else
			{
				swap(xCursor, yCursor, xCursor, yCursor+1);
				isSelecting = !isSelecting;
			}
		}
	}

	if (xCursor < 0) xCursor = 0;
	else if (xCursor > 7) xCursor = 7;

	if (yCursor < 0) yCursor = 0;
	else if (yCursor > 7) yCursor = 7;

	if (isKeyPressed(SDL_SCANCODE_Z) || isKeyPressed(SDL_SCANCODE_X))
	{
		isSelecting = !isSelecting;
	}

	for(int i = 0; i < 8; i++)
	for(int j = 0; j < 8; j++)
	{
		if (i == xCursor && j == yCursor)
		{
			drawRectangle(BASEX+i*16, BASEY+j*16, 17, 17, 2, true);
			if(gems[i][j]) gems[i][j]->draw(BASEX+1+i*16, BASEY+1+j*16, true);
		}
		else
		{
			drawRectangle(BASEX+i*16, BASEY+j*16, 17, 17, 2);
			if (gems[i][j]) gems[i][j]->draw(BASEX+1+i*16, BASEY+1+j*16);
		}
	}
}

enum Dir
{
	LEFT,
	RIGHT,
	UP,
	DOWN
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
		gems[x][y] = new Gem(type);
		gems[x1][y1] = new Gem(type);
		gems[x2][y2] = new Gem(type);
	}
	else return genPartialMatch(rand()%8, rand()%8, type);
}

void Board::avoidMatches()
{
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
		if (!gems[i][j]) gems[i][j] = new Gem(rand()%6+1);
	
	avoidMatches();
	// Run twice to (hopefully) avoid edge cases
	avoidMatches();
}

void Board::swap(int x1, int y1, int x2, int y2)
{
	gems[x1][y1]->isSwapping = true;
	gems[x2][y2]->isSwapping = true;
}