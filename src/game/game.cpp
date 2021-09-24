#include "game/game.h"

#include "game/common.h"

Sprite *test;

Game::Game()
{
	initSound();

	initScreen("Jewels!", XRES, YRES);

	addColorPalette("Amber",   0x0d0405, 0x5e1210, 0xd35600, 0xfed018);
	addColorPalette("Purple",  0x380031, 0x8a157a, 0xc23e80, 0xff9999);
	addColorPalette("Lluv",    0x300030, 0x602878, 0xf89020, 0xf8f088);
	addColorPalette("Meadow",  0x012824, 0x265935, 0xff4d6d, 0xfcdeea);
	addColorPalette("Prastie", 0x622e4c, 0x7550e8, 0x608fcf, 0x8be5ff);

	createTexture("assets/jewel1.pcx", "gem1");
	createTexture("assets/jewel2.pcx", "gem2");
	createTexture("assets/jewel3.pcx", "gem3");
	createTexture("assets/jewel4.pcx", "gem4");
	createTexture("assets/jewel5.pcx", "gem5");
	createTexture("assets/jewel6.pcx", "gem6");

	test = new Sprite("gem1", 15, 15, 6, 200);

	menu = new MainMenu();

	srand(time(NULL));

	board = new Board();
}

bool Game::update()
{
	updateEvents();

	if (isKeyPressed(SDL_SCANCODE_ESCAPE)) return false;

	if (isKeyPressed(SDL_SCANCODE_SPACE)) setNextColorPalette();
	beginDraw();
	if (inMenu)
	{
		if (menu->update()) inMenu = false;
	}
	else
		board->update();
	endDraw();

	return true;
}

Game::~Game()
{
	deinitSound();
	deinitScreen();
}