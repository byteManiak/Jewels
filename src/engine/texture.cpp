#include "engine/texture.h"
#include "engine/screen.h"
#include "engine/color.h"

#include <SDL2/SDL_image.h>
#include <iostream>
#include <unordered_map>

class TextureObject
{
public:
	TextureObject() {}
	TextureObject(std::string path)
	{
		surface = IMG_Load(path.c_str());

		updateTexture();
	}

	~TextureObject()
	{
		SDL_DestroyTexture(texture);
		SDL_FreeSurface(surface);
	}

	void updateTexture()
	{
		// In order for the color palettes to work properly with transparency
		// the surface needs to be converted from indexed to RGBA. The original indexed surface is 
		// kept in memory to be able to re-apply the color palette change when needed.

		SDL_SetSurfacePalette(surface, currentPalette);
		SDL_PixelFormat *pf = SDL_AllocFormat(SDL_PIXELFORMAT_BGRA32);

		SDL_Surface *tempSurface = SDL_ConvertSurface(surface, pf, 0);
		SDL_SetColorKey(tempSurface, SDL_TRUE, 0xFFFFFF);

		if (texture != NULL) SDL_DestroyTexture(texture);
		texture = SDL_CreateTextureFromSurface(renderer, tempSurface);

		SDL_FreeSurface(tempSurface);
		SDL_FreeFormat(pf);
	}

	SDL_Texture *texture = NULL;

private:
	SDL_Surface *surface = NULL;
};

static std::unordered_map<std::string, TextureObject*> textures;

void createTexture(std::string path, std::string name)
{
	if (textures.find(name) != textures.end())
	{
		std::cout << "Texture \"" << path << "\" is already loaded in memory" << std::endl;
		return;
	}

	textures[name] = new TextureObject(path);
}

void deleteTexture(std::string name)
{
	if (textures.find(name) == textures.end())
	{
		std::cout << "Texture \"" << name << "\" was not found in memory" << std::endl;
		return;
	}

	//textures[name]->deleteTexture();
	delete(textures[name]);
	textures.erase(name);
}

void updateTextures()
{
	for(auto &i : textures)
	{
		i.second->updateTexture();
	}
}

void drawTexture(std::string name, int x, int y, int w, int h, int sx, int sy, int sw, int sh)
{
	if (textures.find(name) == textures.end())
	{
		std::cerr << "Texture \"" << name << " is not loaded in memory" << std::endl;
		return;
	}

	SDL_Rect src = {sx, sy, sw, sh};
	SDL_Rect dst = {x, y, w, h};
	if (sx == 0 && sy == 0 && sw == 0 && sh == 0) SDL_RenderCopy(renderer, textures[name]->texture, NULL, &dst);
	else SDL_RenderCopy(renderer, textures[name]->texture, &src, &dst);
}
