#pragma once

#include <string>
#include <SDL2/SDL.h>

typedef struct _ColorPalette
{
	SDL_Color c1, c2, c3, c4;
} ColorPalette;

extern SDL_Palette *currentPalette;

/**
 * @brief Add a new color palette to the existing list of palettes
 *
 * @param palName Name of the color palette
 * @param c1 First color in the palette
 * @param c2 Second color in the palette
 * @param c3 Third color in the palette
 * @param c4 Fourth color in the palette
 */
void addColorPalette(std::string palName, uint32_t c1, uint32_t c2, uint32_t c3, uint32_t c4);

/**
 * @brief Set the current color palette
 *
 * @param palName Name of the palette to use
 */
void setColorPalette(std::string palName, bool force = false);

void setNextColorPalette();

void updatePalette();
