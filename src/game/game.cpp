#include "game/game.h"

#include "game/common.h"

Sprite *test;

Game::Game()
{
	initSound();

	initScreen("Jewels!", XRES, YRES);

	loadFont();

	addColorPalette("Gold", 0x210b1b, 0x4d222c, 0x9d654c, 0xcfab51);
	addColorPalette("Amber", 0x0d0405, 0x5e1210, 0xd35600, 0xfed018);
	addColorPalette("Vboy", 0x000000, 0x550000, 0xa40000, 0xef0000);
	addColorPalette("Nymph", 0x2c2137, 0x446176, 0x3fac95, 0xa1ef8c);
	addColorPalette("Blue", 0x141433, 0x1f1466, 0x4a24b3, 0x8f66cc);

	createTexture("assets/jewel1.pcx", "gem1");
	createTexture("assets/jewel2.pcx", "gem2");
	createTexture("assets/jewel3.pcx", "gem3");
	createTexture("assets/jewel4.pcx", "gem4");
	createTexture("assets/jewel5.pcx", "gem5");
	createTexture("assets/jewel6.pcx", "gem6");
	createTexture("assets/arrows.pcx", "arrows");

	createMusic("assets/music.wav");

	test = new Sprite("gem1", 15, 15, 6, 200);

	menu = new MainMenu();

	srand(time(NULL));

	board = new Board();
}

bool Game::update()
{
	updateEvents();

	if (isKeyPressed(SDL_SCANCODE_ESCAPE)) return false;

	beginDraw();

	if (inMenu)
	{
		if (menu->update())
		{
			inMenu = false;
			board->genBoard();
			playMusic();
		}
	}
	else
	{
		board->update();
	}

	endDraw();

	return true;
}

Game::~Game()
{
	deinitSound();
	deinitScreen();
}