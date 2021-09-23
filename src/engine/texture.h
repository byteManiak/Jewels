#pragma once

#include <string>

/**
 * @brief Create a texture from a file
 * 
 * @param path Path to the texture file
 * @param name Name given to keep track of the texture
 */
void createTexture(std::string path, std::string name);

/**
 * @brief Delete a texture object from memory
 * 
 * @param name Name given to the texture in createTexture() 
 */
void deleteTexture(std::string name);

/**
 * @brief Update texture attributes such as color palette
 */
void updateTextures();

/**
 * @brief Draw a texture with scaling factor
 * 
 * @param name Name of the texture to draw
 * @param x Base X coordinate to draw the texture at
 * @param y Base Y coordinate to draw the texture at
 * @param w Width of the draw output
 * @param h Height of the draw output
 * @param sx Source X offset of the texture
 * @param sy Source Y offset of the texture
 * @param sw Source width starting from X offset of the texture
 * @param sh Source height starting from Y offset of the texture
 */
void drawTexture(std::string name, int x, int y, int w, int h, int sx = 0, int sy = 0, int sw = 0, int sh = 0);