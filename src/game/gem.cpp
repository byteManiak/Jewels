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

void Gem::draw(int x, int y, bool isSelected)
{
	if (isSwapping) return;

	if (isSelected) sprite->draw(x, y);
	else sprite->drawTile(x, y, 0);
}

void Gem::setNextType()
{
	type++;
	if (type > 6) type = 1;
	sprite->setSprite("gem" + std::to_string(type));
}