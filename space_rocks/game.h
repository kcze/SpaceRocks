#pragma once

#include "scenes/scene_game.h"
#include "scenes/scene_menu.h"
#include "audio_manager.h"

#define GAMEX 1280
#define GAMEY 720

extern AudioManager audioManager;
extern MenuScene menuScene;
extern GameScene gameScene;

enum _collisionFlags
{
	EDGE			= 0x0001,
	PLAYER_SHIP		= 0x0002, 
	ENEMY_SHIP		= 0x0004,
	PLAYER_BULLET	= 0x0008,
	ENEMY_BULLET	= 0x0010,
	ASTEROIDS		= 0x0020,
};

