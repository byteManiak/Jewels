#include "game/game.h"

int main(int argc, char **argv)
{
	Game game = Game();

	while(true)
	{
		if (!game.update()) break;
	}

	return 0;
}