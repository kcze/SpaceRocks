#include "audio_manager.h"

std::map<std::string, sf::SoundBuffer> AudioManager::_soundBuffers =
{
	{
		"wave_approaching",
		*Resources::get<sf::SoundBuffer>("wave_approaching.wav")
	},
	{
		"voice_3",
		*Resources::get<sf::SoundBuffer>("voice_3.wav")
	},
	{
		"voice_2",
		*Resources::get<sf::SoundBuffer>("voice_2.wav")
	}, 
	{
		"voice_1",
		*Resources::get<sf::SoundBuffer>("voice_1.wav")
	}, 
	{
		"upgrade_purchased_2",
		*Resources::get<sf::SoundBuffer>("upgrade_purchased_2.wav")
	},
	{
		"upgrade_purchased_1",
		*Resources::get<sf::SoundBuffer>("upgrade_purchased_1.wav")
	},
	{
		"player_hurt",
		*Resources::get<sf::SoundBuffer>("player_hurt.wav")
	},
	{
		"player_death",
		*Resources::get<sf::SoundBuffer>("player_death.wav")
	},
	{
		"pickup_health",
		*Resources::get<sf::SoundBuffer>("pickup_health.wav")
	},
	{
		"pickup_coin",
		*Resources::get<sf::SoundBuffer>("pickup_coin.wav")
	},
	{
		"laser_heavy",
		*Resources::get<sf::SoundBuffer>("laser_heavy.wav")
	},
	{
		"gun_medium",
		*Resources::get<sf::SoundBuffer>("gun_medium.wav")
	},
	{
		"gun_light_2",
		*Resources::get<sf::SoundBuffer>("gun_light_2.wav")
	},
	{
		"gun_light_1",
		*Resources::get<sf::SoundBuffer>("gun_light_1.wav")
	}, 
	{
		"gun_heavy",
		*Resources::get<sf::SoundBuffer>("gun_heavy.wav")
	},
	{
		"game_over",
		*Resources::get<sf::SoundBuffer>("game_over.wav")
	},
	{
		"enemy_death",
		*Resources::get<sf::SoundBuffer>("enemy_death.wav")
	},
	{
		"bullet_impact_light",
		*Resources::get<sf::SoundBuffer>("bullet_impact_light.wav")
	},
	{
		"bullet_impact_heavy",
		*Resources::get<sf::SoundBuffer>("bullet_impact_heavy.wav")
	},
	{
		"menu_cycle",
		*Resources::get<sf::SoundBuffer>("menu_cycle.wav")
	},
	{
		"menu_select",
		*Resources::get<sf::SoundBuffer>("menu_select.wav")
	},
	{
		"asteroid_broken",
		*Resources::get<sf::SoundBuffer>("asteroid_broken.wav")
	},
	{
		"bullet_x_bullet",
		*Resources::get<sf::SoundBuffer>("bullet_x_bullet.wav")
	},
	{
		"not_enough_coins",
		*Resources::get<sf::SoundBuffer>("not_enough_coins.wav")
	}	
};

sf::Sound AudioManager::_sounds[10] = { sf::Sound()};

void AudioManager::playSound(std::string name) { 
	_soundQueue.push(name);
}

void AudioManager::update(double dt)
{
	_playSound();
}



void AudioManager::_playSound()
{
	while (!_soundQueue.empty())
	{
		std::string name = _soundQueue.front();
		_soundQueue.pop();
		_soundIndex = _soundIndex > 9 ? 0 : _soundIndex;
		_sounds[_soundIndex].setBuffer(_soundBuffers[name]);
		_sounds[_soundIndex].play();
		_soundIndex++;
		std::cout << "Playing Sound: " << name << std::endl;
	}
}

AudioManager audioManager;