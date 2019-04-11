#pragma once

#include "ecm.h"

class ShipFactory {
public:
	static std::shared_ptr<Entity> makePlayer();
	static std::shared_ptr<Entity> makeEnemy();
	static std::shared_ptr<Entity> makeShip();

private:
	ShipFactory() {}
};