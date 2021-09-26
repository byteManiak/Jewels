#pragma once

#include <string>

void initSound();
void deinitSound();
void createSound(std::string path, std::string name);
void deleteSound(std::string name);
int playSound(std::string name);
void stopSound(int channel);
bool isSoundPlaying(int channel);
void createMusic(std::string path);
void deleteMusic();
void playMusic();
void pauseMusic();
void resumeMusic();