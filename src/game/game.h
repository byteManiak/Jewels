#include "game/mainmenu.h"
#include "game/gem.h"

class Game
{
public:
	Game();
	~Game();
	bool update();

private:
	MainMenu *menu;
};