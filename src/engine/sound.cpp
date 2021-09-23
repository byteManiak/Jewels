#include "engine/sound.h"

#include <SDL2/SDL_mixer.h>
#include <unordered_map>
#include <iostream>

std::unordered_map<std::string, Mix_Chunk*> sounds;

void initSound()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		std::cerr << "Could not initialize audio" << std::endl;
		return;
	}
}

void deinitSound()
{
	for(auto &i : sounds) Mix_FreeChunk(i.second);
	Mix_CloseAudio();
}

void createSound(std::string path, std::string name)
{
	Mix_Chunk *sound = Mix_LoadWAV(path.c_str());
	if (sound == NULL)
	{
		std::cerr << "Could not load audio from \"" << path << "\"" << std::endl;
		return;
	}
	sounds[name] = sound;
}

void deleteSound(std::string name)
{
	if (sounds.find(name) == sounds.end())
	{	
		std::cout << "Sound \"" << name << "\" was not found in memory" << std::endl;
		return;
	}

	Mix_FreeChunk(sounds[name]);
	sounds.erase(name);
}

int playSound(std::string name)
{
	if (sounds.find(name) == sounds.end())
	{
		std::cerr << "No sound named \"" << name << "\" is currently loaded in memory" << std::endl;
		return -2;
	}

	return Mix_PlayChannel(-1, sounds[name], 0);
}

bool isSoundPlaying(int channel)
{
	return Mix_Playing(channel) != 0;
}