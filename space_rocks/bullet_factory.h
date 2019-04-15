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
#include "factory.h"

class BulletFactory : Factory {
public:
	static std::shared_ptr<Entity> makeBullet(unsigned int id);

private:
	BulletFactory() {}

	static std::map < unsigned int, ObjectData> _objectData;
};