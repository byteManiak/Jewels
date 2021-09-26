#pragma once

#include "game/common.h"

#include <string>

class Bar
{
public:
	Bar();
	~Bar();

	void addProgress();
	void draw();

	bool startNewLevel = false;
private:
	int maxgems = 60;
	int gemcount = 0;
};