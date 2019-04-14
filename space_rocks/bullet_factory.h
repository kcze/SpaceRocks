#pragma once

#include "ecm.h"
#include "components\cmp_sprite.h"
#include "components\cmp_physics.h"
#include "components\cmp_destructible.h"
#include "components\cmp_bullet.h"
#include "engine.h"
#include "game.h"
#include "system_resources.h"
#include <string>
#include "Box2D/Box2D.h"
#include "system_physics.h"

struct ObjectData
{
	std::vector<b2Vec2 > _coords;
	std::shared_ptr<sf::Texture> _tex;
	sf::IntRect _texRect;
};

class BulletFactory {
public:
	static std::shared_ptr<Entity> makeBullet(unsigned int id);

private:
	BulletFactory() {}
	static const float PSI4;

	static std::map < unsigned int, ObjectData> _objectData;
};