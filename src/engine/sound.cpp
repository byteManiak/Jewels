#include "engine/sound.h"

#include <SDL2/SDL_mixer.h>
#include <unordered_map>
#include <string>

class Sound
{
private:
	Mix_Chunk *sound;
};

//std::unordered_map<std::string, Sound> sounds;
//void playSound(std::string name);