#pragma once

#include <string>

enum GemType
{
	DIAMOND,
	EMERALD,
	RUBY,
	TOPAZ,
	SAPPHIRE,
	AMETHYST,
	GARNET
};

class Gem
{
	Gem(GemType gemType);
private:
	std::string texture;
};