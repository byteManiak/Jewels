#include "game/game.h"

#include "game/common.h"

#include <ctime>

Sprite *test;

Game::Game()
{
	initInput();

	initSound();

	initScreen("Jewels!", XRES, YRES);

	loadFont();

	addColorPalette("Gold", 0x210b1b, 0x3d223c, 0x8d655c, 0xbfab61);
	addColorPalette("Amber", 0x0d0405, 0x5e1210, 0xd35600, 0xfed018);
	addColorPalette("Vboy", 0x000000, 0x552222, 0xa44444, 0xff7777);
	addColorPalette("Nymph", 0x2c2137, 0x446176, 0x3fac95, 0xa1ef8c);
	addColorPalette("Blue", 0x141444, 0x1f1488, 0x4a24cc, 0x8f66ff);

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

	beginDraw();

	if (inMenu)
	{
		if (menu->update())
		{
			inMenu = false;
			board->loadGame();
			playMusic();
		}
	}
	else
	{
		if (board->update()) return false;
	}

	endDraw();

	return true;
}

Game::~Game()
{
	deinitSound();
	deinitScreen();
}
