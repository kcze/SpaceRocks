#pragma once

#include "ecm.h"
#include "engine.h"
#include "game.h"
#include "components\cmp_sprite.h"
#include "components\cmp_physics.h"
#include "components\cmp_ship.h"
#include "components\cmp_destructible.h"
#include "components\cmp_player.h"
#include "system_resources.h"
#include "Box2D/Box2D.h"
#include <string>
#include "system_physics.h"

struct ObjectData
{
	std::vector<b2Vec2 > _coords;
	std::shared_ptr<sf::Texture> _tex;
	sf::IntRect _texRect;
};

class ShipFactory {
public:
	static std::shared_ptr<Entity> makePlayer();
	static std::shared_ptr<Entity> makeEnemy(unsigned int type);
	static std::shared_ptr<Entity> makeShip();

private:
	ShipFactory() {}
	static std::map < unsigned int, ObjectData> _objectData;
	static const float PSI8;
};

const float  ShipFactory::PSI8 = Physics::physics_scale_inv * 16.0f;