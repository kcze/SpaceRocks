#pragma once

#include "ecm.h"
#include "engine.h"
#include "game.h"
#include "components\components.h"
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