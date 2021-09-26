#include "game/score.h"

#include "engine/text.h"

#define SCOREX 67
#define SCOREY 132

Score::Score()
{
	sz = "0000000";
}

Score::~Score()
{

}

void Score::addScore(int combo)
{
	score += combo * (level*5);
	std::string s = std::to_string(score);
	sz = std::string(7-s.length(),'0') + s;
}

void Score::draw()
{
	drawText(sz, SCOREX, SCOREY);
}

void Score::increaseLevel()
{
	level++;
}