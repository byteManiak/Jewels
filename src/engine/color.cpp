#include "engine/color.h"
#include "engine/texture.h"

#include <unordered_map>

static std::unordered_map<std::string, ColorPalette> colorPalettes;
static std::unordered_map<std::string, ColorPalette>::iterator currentPaletteIndex;
SDL_Palette *currentPalette = NULL;
SDL_Palette *internalPalette = NULL;
// Used for smooth color transitions
float fcolors[4][3];

void addColorPalette(std::string palName, uint32_t c1, uint32_t c2, uint32_t c3, uint32_t c4)
{
	colorPalettes[palName] = {
		{(c1 & 0xff0000) >> 16, (c1 & 0xff00) >> 8, c1 & 0xff, 0},
		{(c2 & 0xff0000) >> 16, (c2 & 0xff00) >> 8, c2 & 0xff, 0},
		{(c3 & 0xff0000) >> 16, (c3 & 0xff00) >> 8, c3 & 0xff, 0},
		{(c4 & 0xff0000) >> 16, (c4 & 0xff00) >> 8, c4 & 0xff, 0},
	};
}

int startTick;

void setColorPalette(std::string palName, bool force)
{
	auto requestedPalette = colorPalettes.find(palName);
	if (requestedPalette == colorPalettes.end())
	{
		setColorPalette("Default");
		return;
	}

	currentPaletteIndex = requestedPalette;

	if (internalPalette == NULL) internalPalette = SDL_AllocPalette(5);

	ColorPalette palette = requestedPalette->second;
	internalPalette->colors[0] = palette.c1;
	internalPalette->colors[1] = palette.c2;
	internalPalette->colors[2] = palette.c3;
	internalPalette->colors[3] = palette.c4;
	// Fifth color index is a dummy and used as alpha
	internalPalette->colors[4] = {0xFF, 0xFF, 0xFF, 0};

	if (force)
	{
		if (currentPalette == NULL) currentPalette = SDL_AllocPalette(5);
		currentPalette->colors[0] = palette.c1;
		currentPalette->colors[1] = palette.c2;
		currentPalette->colors[2] = palette.c3;
		currentPalette->colors[3] = palette.c4;
		// Fifth color index is a dummy and used as alpha
		currentPalette->colors[4] = {0xFF, 0xFF, 0xFF, 0};

		fcolors[0][0] = palette.c1.r;
		fcolors[0][1] = palette.c1.g;
		fcolors[0][2] = palette.c1.b;
		fcolors[1][0] = palette.c2.r;
		fcolors[1][1] = palette.c2.g;
		fcolors[1][2] = palette.c2.b;
		fcolors[2][0] = palette.c3.r;
		fcolors[2][1] = palette.c3.g;
		fcolors[2][2] = palette.c3.b;
		fcolors[3][0] = palette.c4.r;
		fcolors[3][1] = palette.c4.g;
		fcolors[3][2] = palette.c4.b;
	}

	startTick = SDL_GetTicks();
}

void lerp(float &c, float d)
{
	// Scale the lerp speed with the distance for a smooth animation
	float distance = abs(c-d);
	float lerpSpeed = distance * (SDL_GetTicks() - startTick)/1500.f;

	// Move radial menu towards the new destination
	if (c > d) c -= lerpSpeed;
	else c += lerpSpeed;
}

void updatePalette()
{
    for(int i = 0; i < 4; i++)
    {
		SDL_Color dest = internalPalette->colors[i];
		lerp(fcolors[i][0], dest.r);
		lerp(fcolors[i][1], dest.g);
		lerp(fcolors[i][2], dest.b);
		currentPalette->colors[i].r = fcolors[i][0];
		currentPalette->colors[i].g = fcolors[i][1];
		currentPalette->colors[i].b = fcolors[i][2];
    }

	startTick = SDL_GetTicks();

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
