#pragma once

#include "engine/engine.h"

/**
 * @brief Initialize the TTF library.
 */
void initTTF();

/**
 * @brief Create a font from a file.
 *
 * @param path Path to the font file
 * @param fontSize Size to load the font with
 * @param name Name given to keep track of the font
 */
void createFont(std::string path, int fontSize, std::string name);

/**
 * @brief Set the current font used by drawText.
 * @param name Name of the font.
 */
void setFont(std::string name);

/**
 * @brief Draw a text string at the given coordinates.
 */
void drawText(std::string text, int x, int y);