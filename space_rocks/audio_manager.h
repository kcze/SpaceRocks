#pragma once

#include "ecm.h"
#include "system_resources.h"
#include "engine.h"
#include <queue>

// Plays all sounds
class AudioManager {
public:

	void playSound(std::string name);
	AudioManager() {}
	void update(double dt);

private:

	void _playSound();
	static std::map<std::string, sf::SoundBuffer> _soundBuffers;
	static sf::Sound _sounds[30];
	unsigned int _soundIndex = 0;
	std::queue<std::string> _soundQueue;

};