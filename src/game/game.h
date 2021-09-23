#include "game/mainmenu.h"
#include "game/board.h"

class Game
{
public:
	Game();
	~Game();
	bool update();

private:
	MainMenu *menu;
	Board *board;
};