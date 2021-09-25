#pragma once

#include "game/common.h"

class Score
{
public:
	Score();
	~Score();

	void addScore(int combo);
	void draw();

private:
	int level = 1;
	int score = 0;
};