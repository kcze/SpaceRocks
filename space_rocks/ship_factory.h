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
#include "factory.h"

class ShipFactory : Factory {
public:
	static std::shared_ptr<Entity> makePlayer();
	static std::shared_ptr<Entity> makeEnemy(unsigned int type);
	static std::shared_ptr<Entity> makeShip();

private:
	ShipFactory() {}
	static std::map < unsigned int, ObjectData> _objectData;
};