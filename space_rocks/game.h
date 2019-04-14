#pragma once

#include "scenes/scene_game.h"
#include "scenes/scene_menu.h"

#define GAMEX 1280
#define GAMEY 720

extern MenuScene menuScene;
extern GameScene gameScene;

enum _collisionFlags
{
	EDGE			= 0x0001,
	PLAYER_SHIP		= 0x0002,
	ENEMY_SHIP		= 0x0003,
	PLAYER_BULLET	= 0x0004,
	ENEMY_BULLET	= 0x0005,
	ASTEROIDS		= 0x0006,
};
