#pragma once

#include "factory.h"
#include "ecm.h"
#include "components\cmp_sprite.h"
#include "components\cmp_physics.h"
#include "components\cmp_destructible.h"
#include "system_resources.h"
#include "engine.h"
#include "game.h"
#include "Box2D/Box2D.h"
#include "system_physics.h"

// Creates particles
class ParticleFactory : Factory {
public:
	static std::shared_ptr<Entity> makeParticle(unsigned int type);

private:
	ParticleFactory() {}

	static std::map < unsigned int, ObjectData> _objectData;
};