#include "engine/color.h"
#include "engine/texture.h"

#include <unordered_map>

static std::unordered_map<std::string, ColorPalette> colorPalettes;
static std::unordered_map<std::string, ColorPalette>::iterator currentPaletteIndex;
SDL_Palette *currentPalette = NULL;

void addColorPalette(std::string palName, uint32_t c1, uint32_t c2, uint32_t c3, uint32_t c4)
{
	colorPalettes[palName] = {
		{(c1 & 0xff0000) >> 16, (c1 & 0xff00) >> 8, c1 & 0xff, 0},
		{(c2 & 0xff0000) >> 16, (c2 & 0xff00) >> 8, c2 & 0xff, 0},
		{(c3 & 0xff0000) >> 16, (c3 & 0xff00) >> 8, c3 & 0xff, 0},
		{(c4 & 0xff0000) >> 16, (c4 & 0xff00) >> 8, c4 & 0xff, 0},
	};
}

void setColorPalette(std::string palName)
{
	auto requestedPalette = colorPalettes.find(palName);
	if (requestedPalette == colorPalettes.end())
	{
		setColorPalette("Default");
		return;
	}

	currentPaletteIndex = requestedPalette;

	if (currentPalette == NULL) currentPalette = SDL_AllocPalette(5);

	ColorPalette palette = requestedPalette->second;
	currentPalette->colors[0] = palette.c1;
	currentPalette->colors[1] = palette.c2;
	currentPalette->colors[2] = palette.c3;
	currentPalette->colors[3] = palette.c4;
	// Fifth color index is a dummy and used as alpha
	currentPalette->colors[4] = {0xFF, 0xFF, 0xFF, 0};

	updateTextures();
}

void setNextColorPalette()
{
	if (std::next(currentPaletteIndex) == colorPalettes.end())
	{
		currentPaletteIndex = colorPalettes.begin();
	}
	else currentPaletteIndex = std::next(currentPaletteIndex);

	setColorPalette(currentPaletteIndex->first);
}