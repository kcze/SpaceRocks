#pragma once

#include "ecm.h"
#include <map>
#include "Box2D/Box2D.h"
#include "system_physics.h"
#include "game.h"
#include "engine.h"
#include "components\cmp_sprite.h"
#include "components\cmp_physics.h"
#include "components\cmp_destructible.h"
#include "system_resources.h"
#include <string>

struct ObjectData
{
	std::vector<b2Vec2 > _coords;
	std::shared_ptr<sf::Texture> _tex;
	sf::IntRect _texRect;
};

class AsteroidFactory {
public:
	static std::shared_ptr<Entity> makeAsteroid(unsigned int id);

protected:
	AsteroidFactory() {}

	static const float PSI16; 
	static std::map < unsigned int, ObjectData> _objectData;

};