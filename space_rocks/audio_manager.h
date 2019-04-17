#pragma once

#include "ecm.h"
#include "system_resources.h"
#include "engine.h"

class AudioManager {
public:

	void playSound(std::string name);
	AudioManager() {}


private:

	static std::map<std::string, sf::SoundBuffer> _soundBuffer;
	sf::Sound testSound;
};