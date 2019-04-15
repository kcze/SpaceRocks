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
#include "factory.h"

class AsteroidFactory : Factory {
public:
	static std::shared_ptr<Entity> makeAsteroid(unsigned int id, b2Vec2 coords);

protected:
	AsteroidFactory() {}

	static std::map < unsigned int, ObjectData> _objectData;

};