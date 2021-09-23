#include "game/gem.h"

Gem::Gem(int type)
{
	sprite = new Sprite("gem" + std::to_string(type), 15, 15, 6, 100); 
	this->type = type;
}

Gem::~Gem()
{
	delete(sprite);
}

void Gem::draw(int x, int y)
{
	if (isSelected) sprite->draw(x, y);
	else sprite->drawTile(x, y);
}