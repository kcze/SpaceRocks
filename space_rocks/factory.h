#pragma once

#include "Box2D/Box2D.h"
#include "system_physics.h"
#include "engine.h"
#include "game.h"
#include "ecm.h"


struct ObjectData
{
	std::vector<b2Vec2 > _coords;
	std::shared_ptr<sf::Texture> _tex;
	sf::IntRect _texRect;
};

class Factory {
protected:
	static const float PSI4;
	static const float PSI8;
	static const float PSI16;
};