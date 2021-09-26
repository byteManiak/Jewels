#pragma once

#include "game/common.h"

#include <string>

class Score
{
public:
	Score();
	~Score();

	void addScore(int combo);
	void draw();
	void increaseLevel();
	void reset();

private:
	int level = 1;
	int score = 0;
	std::string s, l;
};