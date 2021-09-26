#include "game/score.h"

#include "engine/text.h"

#define SCOREX 100
#define SCOREY 132
#define LEVELX 6
#define LEVELY 132

Score::Score()
{
	s = "0000000";
	l = "001";
}

Score::~Score()
{

}

void Score::addScore(int combo)
{
	score += combo * (level*5);
	std::string t = std::to_string(score);
	s = std::string(7-t.length(),'0') + t;
}

void Score::draw()
{
	drawText("level", LEVELX, LEVELY);
	drawText(l, LEVELX+48, LEVELY);
	drawText(s, SCOREX, SCOREY);
}

void Score::increaseLevel()
{
	level++;
	std::string t = std::to_string(level);
	l = std::string(3-t.length(),'0') + t;
}

void Score::reset()
{
	level = 1;
	score = 0;
	s = "0000000";
	l = "001";
}