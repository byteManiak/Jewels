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

void drawTexture(std::string name, int x, int y, int w, int h, int sx = 0, int sy = 0, int sw = 0, int sh = 0);