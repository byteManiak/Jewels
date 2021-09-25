#include "game/score.h"

#include "engine/text.h"

#include <string>

#define SCOREX 67
#define SCOREY 132

Score::Score()
{

}

Score::~Score()
{

}

void Score::addScore(int combo)
{
	score += combo * (level*5);
}

void Score::draw()
{
	std::string s = std::to_string(score);
	std::string sz = std::string(7-s.length(),'0') + s;
	drawText(sz, SCOREX, SCOREY);
}