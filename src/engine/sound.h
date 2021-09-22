#pragma once

#include <string>

void initSound();
void deinitSound();
void createSound(std::string path, std::string name);
void deleteSound(std::string name);
int playSound(std::string name);
bool isSoundPlaying(int channel);