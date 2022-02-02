#include "game/mainmenu.h"

#include "game/common.h"

#include <iostream>
#include <cmath>

class SpinnyGem
{
public:
	SpinnyGem(int type)
	{
		sprite = new Sprite("gem" + std::to_string(type), 15, 15, 6, 100);
		startTick = SDL_GetTicks();
	}

	void update()
	{
		int x, y;
		if (!isLooping)
		{
			x = -15 + (SDL_GetTicks() - startTick) / 20.f;
			y = YCENTRE/3-9;
			if (x >= XCENTRE-7)
			{
				x = XCENTRE-7;
				startTick = SDL_GetTicks();
				isLooping = true;
			}
		}
		else
		{
			x = XCENTRE-7+sin((SDL_GetTicks() - startTick) / 600.f)*(3*XCENTRE/4.f);
			y = YCENTRE-21-cos((SDL_GetTicks() - startTick) / 600.f)*(YCENTRE/2.f);
		}

		sprite->draw(x, y);
	}

private:
	int startTick;
	bool isLooping = false;
	Sprite *sprite;
};

MainMenu::MainMenu()
{
	startTick = SDL_GetTicks();

	createTexture("assets/logo.pcx", "logo");
	createSound("assets/intro.wav", "intro");
	soundChannel = playSound("intro");
}

#define LOGO_SIZE_X 47
#define LOGO_SIZE_Y 26

bool MainMenu::update()
{
	bool retVal = false;

	if (logoMoving)
	{
		logoY = -LOGO_SIZE_Y*2 + (SDL_GetTicks() - startTick) / 40.f;
		if (logoY >= YCENTRE - LOGO_SIZE_Y - 18) logoMoving = false;
		if (isKeyPressed(SDL_SCANCODE_RETURN)) logoMoving = false;
	}
	else
	{
		logoY = YCENTRE - LOGO_SIZE_Y - 18;
		if ((SDL_GetTicks() - startTick) > 620)
		{
			startTick = SDL_GetTicks();
			if (gems.size() < 6)
			{
				gems.push_back(SpinnyGem(gems.size()+1));
			}
		}

		if (isKeyPressed(SDL_SCANCODE_RETURN))
		{
			stopSound(soundChannel);
			retVal = true;
		}

		drawText("a game by bytemaniak", 6, 1);

		drawText("press enter to play", 10, 100);
	}

	drawTexture("logo", 31, logoY, LOGO_SIZE_X*2, LOGO_SIZE_Y*2, 0, 0, LOGO_SIZE_X, LOGO_SIZE_Y);
	for(auto &i : gems) i.update();

	return retVal;
}
