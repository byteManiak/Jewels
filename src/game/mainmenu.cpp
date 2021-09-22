#include "game/mainmenu.h"

#include "game/common.h"

#include <iostream>

class SpinnyGem
{
public:
	SpinnyGem(int type)
	{
		texture = "gem" + std::to_string(type);
		startTick = SDL_GetTicks();
	}

	void update()
	{
		int x, y;
		if (!isLooping)
		{
			x = -15 + (SDL_GetTicks() - startTick) / 20.f;
			y = YCENTRE/3+1;
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
			y = YCENTRE-11-cos((SDL_GetTicks() - startTick) / 600.f)*(YCENTRE/2.f);
		}

		drawTexture(texture, x, y, 15, 15, 15 * ((SDL_GetTicks() - startTick)/100%6), 0, 15, 15);
	}

private:
	int startTick;
	bool isLooping = false;
	std::string texture;
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
		if (logoY >= YCENTRE - LOGO_SIZE_Y - 8) logoMoving = false;
	}
	else
	{
		logoY = YCENTRE - LOGO_SIZE_Y - 8;
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
			std::cout << "Yay" << std::endl;
			retVal = true;
		}
	}

	drawTexture("logo", 31, logoY, LOGO_SIZE_X*2, LOGO_SIZE_Y*2, 0, 0, LOGO_SIZE_X, LOGO_SIZE_Y);
	for(auto &i : gems) i.update();

	return false;
}