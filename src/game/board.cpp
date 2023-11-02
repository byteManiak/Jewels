#include "game/board.h"

#include <fstream>

enum PauseReturn
{
	NONE,
	NEWGAME,
	QUIT
};

#define PAUSEY 42

class PauseMenu
{
public:
	PauseReturn update()
	{
		if (isKeyPressed(SDL_SCANCODE_DOWN)) menuCursor++;
		if (isKeyPressed(SDL_SCANCODE_UP)) menuCursor--;
		if (menuCursor < 0) menuCursor = 0;
		else if (menuCursor > 3) menuCursor = 3;

		if (isKeyPressed(SDL_SCANCODE_RETURN))
		{
			switch(menuCursor)
			{
				case 0: return NEWGAME;
				case 1:
				{
					soundMuted = !soundMuted;
					muteSounds(soundMuted);
					break;
				}
				case 2:
				{
					musicMuted = !musicMuted;
					muteMusic(musicMuted);
					break;
				}
				case 3: return QUIT;
			}
		}

		drawRectangle(0, PAUSEY-2, 160, 1, 1, true);
		drawRectangle(0, PAUSEY-1, 160, 49, 2, true);
		drawRectangle(0, PAUSEY+47, 160, 1, 1, true);
		drawText("pause", XCENTRE-20, PAUSEY);

		drawText("new game", XCENTRE-32, PAUSEY+8);

		drawText("sounds", XCENTRE-24, PAUSEY+16);
		if (!soundMuted) drawText("x", XCENTRE+32, PAUSEY+16);
		drawText("music", XCENTRE-20, PAUSEY+24);

		if (!musicMuted) drawText("x", XCENTRE+24, PAUSEY+24);

		drawText("save and quit", XCENTRE-48, PAUSEY+32);

		drawText("-", 24, PAUSEY+(menuCursor+1)*8);

		return NONE;
	}

private:
	int menuCursor = 0;
	bool soundMuted = false;
	bool musicMuted = false;
};

class ProgressGem
{
public:
	ProgressGem(int type, int x, int y)
	{
		this->x = x; this->y = y;
		texture = "gem" + std::to_string(type);
		startTick = SDL_GetTicks();
	}

	void draw()
	{
		float dx = abs(x-xdest)+1;
		float dy = abs(y-ydest)+1;

		if ((int)x < xdest)
		{
			x += dx*(SDL_GetTicks() - startTick)/2000.f;
			if (x > xdest) x = xdest;
		}
		else if ((int)x > xdest)
		{
			x -= dx*(SDL_GetTicks() - startTick)/2000.f;
			if (x < xdest) x = xdest;
		}

		if ((int)y < ydest)
		{
			y += dy*(SDL_GetTicks() - startTick)/2000.f;
			if (y > ydest) y = ydest;
		}
		else if ((int)y > ydest)
		{
			y -= dy*(SDL_GetTicks() - startTick)/2000.f;
			if (y < ydest) y = ydest;
		}

		if ((int)x == xdest && (int)y == ydest) reached = true;

		drawTexture(texture, x, y, 15, 15, 0, 0, 15, 15);
	}

	bool reached = false;
private:
	int startTick;
	int xdest = 8, ydest = 4;
	int x, y;
	std::string texture;
};

Board::Board()
{
	for(int i = 0; i < 8; i++)
		createSound("assets/combo"+std::to_string(i)+".wav", "combo"+std::to_string(i));
	createSound("assets/levelup.wav", "levelup");
	createSound("assets/gameover.wav", "gameover");

	pauseMenu = new PauseMenu();
}

Board::~Board()
{
	for(int i = 0; i < 8; i++)
	for(int j = 0; j < 8; j++)
		delete gems[i][j];
}

bool Board::update()
{
	std::pair<int,int> mouseCoords = getMouseCoords();
	mouseX = mouseCoords.first;
	mouseY = mouseCoords.second;

	if (gameover)
	{
		pauseMusic();
		if (isKeyPressed(SDL_SCANCODE_RETURN))
		{
			newGame();
			resumeMusic();
		}
	}
	else if (isPaused)
	{
		if (isKeyPressed(SDL_SCANCODE_ESCAPE)) isPaused = false;
	}
	else
	{
		if (isKeyPressed(SDL_SCANCODE_ESCAPE)) isPaused = true;

		else
		{
			isSelecting = isInBounds(mouseX, mouseY, BASEX, BASEY, BASEX+BWIDTH, BASEY+BWIDTH) && isMouseButtonPressed(LEFT_CLICK);

			if (!isSelecting)
			{
				xCursor = (mouseX-BASEX)/16;
				yCursor = (mouseY-BASEY)/16;
			}
			else if (!isAnimating && !shortWait && swapState == NO_SWAP)
			{
				if (isMouseAtCoords(xCursor-1, yCursor))
				{
					if (xCursor > 0) swap(xCursor, yCursor, xCursor-1, yCursor, true);
				}
				else if (isMouseAtCoords(xCursor+1, yCursor))
				{
					if (xCursor < 7) swap(xCursor, yCursor, xCursor+1, yCursor, true);
				}
				else if (isMouseAtCoords(xCursor, yCursor-1))
				{
					if (yCursor > 0) swap(xCursor, yCursor, xCursor, yCursor-1, true);
				}
				else if (isMouseAtCoords(xCursor, yCursor+1))
				{
					if (yCursor < 7) swap(xCursor, yCursor, xCursor, yCursor+1, true);
				}
			}

			if (xCursor < 0) xCursor = 0;
			else if (xCursor > 7) xCursor = 7;

			if (yCursor < 0) yCursor = 0;
			else if (yCursor > 7) yCursor = 7;
		}
	}

	isAnimating = false;

	for(int i = 0; i < 8; i++)
	for(int j = 0; j < 8; j++)
	{
		drawRectangle(BASEX+i*16, BASEY+j*16, 17, 17, 1);

		if (i == xCursor && j == yCursor)
		{
			drawRectangle(BASEX+i*16+1, BASEY+j*16+1, 15, 15, isSelecting ? 3 : 1, true);
			if(gems[i][j])
			{
				gems[i][j]->draw(true);
				if (gems[i][j]->isMoving) isAnimating = true;
			}
		}
		else
		{
			if (gems[i][j])
			{
				gems[i][j]->draw();
				if (gems[i][j]->isMoving) isAnimating = true;
			}
		}
	}

	findMatch(false);

	if (!isAnimating)
	{
		if (shortWait)
		{
			if (SDL_GetTicks() - waitTick > 900 || !hasMatch)
			{
				shortWait = false;
			}

			for(int i = 0; i < 8; i++)
			for(int j = 0; j < 8; j++)
			if (gems[i][j]->isMatched)
			{
				drawRectangle(BASEX+i*16+1, BASEY+j*16+1, 15, 15, 3, true);
				gems[i][j]->draw(true);
			}
		}
		else
		{
			if (swapState == SWAP_FIRST)
			{
				if (hasMatch) swapState = NO_SWAP;
				else swap(x1swap, y1swap, x2swap, y2swap, true);
			}
			else if (swapState == SWAP_BACK) swapState = NO_SWAP;

			if (hasMatch)
			{
				combo++;
				playSound("combo" + std::to_string(combo > 7 ? 7 : combo));
				sweepMatches();
			}
			else combo = -1;
		}
	}

	score.draw();
	bar.draw();

	for(auto it = progressGems.begin(); it != progressGems.end();)
	{
		it->draw();
		if (it->reached)
		{
			bar.addProgress();

			if (bar.startNewLevel)
			{
				bar.startNewLevel = false;
				score.increaseLevel();
				playSound("levelup");
				setNextColorPalette();
			}

			it = progressGems.erase(it);
		}
		else ++it;
	}

	if (gameover)
	{
		drawRectangle(0, 63, 160, 1, 1, true);
		drawRectangle(0, 64, 160, 25, 2, true);
		drawRectangle(0, 88, 160, 1, 1, true);
		drawText("game over", 48, 67);
		drawText("press enter to reset", 1, 75);
	}

	if (isPaused)
	{
		PauseReturn ret = pauseMenu->update();
		if (ret == NEWGAME)
		{
			newGame();
			isPaused = false;
		}
		else if (ret == QUIT)
		{
			saveGame();
			return true;
		}
	}

	return false;
}

void Board::newGame()
{
	genBoard();
	score.reset();
	bar.reset();
	gameover = false;
}

void Board::saveGame()
{
	std::ofstream file;
	file.open(".savegame", std::ios::binary);
	file.write((char*)&score.level, sizeof(int));
	file.write((char*)&score.score, sizeof(int));
	file.write((char*)&bar.gemcount, sizeof(int));
	file.write((char*)&bar.maxgems, sizeof(int));
	for(int i = 0; i < 8; i++)
	for(int j = 0; j < 8; j++)
		file.write((char*)&gems[i][j]->type, sizeof(int));
	file.close();
}

void Board::loadGame()
{
	if (!tryLoadGame()) newGame();
}

bool Board::tryLoadGame()
{
	std::ifstream file;
	file.open(".savegame", std::ios::binary);
	if (!file.good()) return false;

	file.read((char*)&score.level, sizeof(int));
	file.read((char*)&score.score, sizeof(int));
	file.read((char*)&bar.gemcount, sizeof(int));
	file.read((char*)&bar.maxgems, sizeof(int));

	for(int i = 0; i < 8; i++)
	for(int j = 0; j < 8; j++)
	{
		int type;
		file.read((char*)&type, sizeof(int));
		gems[i][j] = new Gem(type, i, j);
	}

	file.close();

	score.addScore(0);
	score.setLevel();

	for(int i = 0; i < (score.level-1)%6; i++) setNextColorPalette();

	findMatch(false);
	sweepMatches();

	return true;
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
	{
		int gemsMatched = 0;
		for(int j = 0; j < 8; j++)
		{
			if (gems[i][j]->isMatched)
			{
				progressGems.push_back(ProgressGem(gems[i][j]->type,BASEX+i*16,BASEY+j*16));

				delete(gems[i][j]);
				gems[i][j] = nullptr;

				for (int k = j; k > 0; k--)
					swap(i, k, i, k-1, false);

				gems[i][0] = new Gem(rand()%6+1, i, 0, gemsMatched);
				gemsMatched++;

				shortWait = true;
				waitTick = SDL_GetTicks();

				score.addScore(combo+1);
			}
		}
	}

	checkGameover();
	if (gameover) playSound("gameover");
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

void Board::checkGameover()
{
	gameover = true;

	// Check matches of type
	// X X Y
	// Y Z X
	// or
	// X Y X
	// Z X Z
	for(int i = 0; i < 7; i++)
	{
		int occurences[6] = {};
		for(int j = 0; j < 8; j++)
		{
			for(int k = 1; k <= 6; k++)
			{
				if (gems[i][j]->type == k || gems[i+1][j]->type == k)
				{
					occurences[k-1]++;
					if(occurences[k-1] >= 3) gameover = false;
				}
				else occurences[k-1] = 0;
			}
		}
	}

	for(int j = 0; j < 7; j++)
	{
		int occurences[6] = {};
		for(int i = 0; i < 8; i++)
		{
			for(int k = 1; k <= 6; k++)
			{
				if (gems[i][j]->type == k || gems[i][j+1]->type == k)
				{
					occurences[k-1]++;
					if(occurences[k-1] >= 3) gameover = false;
				}
				else occurences[k-1] = 0;
			}
		}
	}

	// Check matches of type
	// X X Y X
	// or
	// X Y X X
	for(int i = 0; i < 5; i++)
	for(int j = 0; j < 8; j++)
	{
		if (gems[i][j]->type == gems[i+3][j]->type &&
			(gems[i][j]->type == gems[i+1][j]->type ||
			 gems[i][j]->type == gems[i+2][j]->type))
			 {
				 gameover = false;
			 }
	}

	for(int j = 0; j < 5; j++)
	for(int i = 0; i < 8; i++)
	{
		if (gems[i][j]->type == gems[i][j+3]->type &&
			(gems[i][j]->type == gems[i][j+1]->type ||
			 gems[i][j]->type == gems[i][j+2]->type))
			 {
				 gameover = false;
			 }
	}
}

bool Board::isMouseAtCoords(int x, int y)
{
	return isInBounds(mouseX, mouseY, BASEX+x*16, BASEY+y*16, BASEX+(x+1)*16, BASEY+(y+1)*16);
}
