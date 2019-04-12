#pragma once

#include "ecm.h"

class BulletFactory {
public:
	static std::shared_ptr<Entity> makeBullet();

private:
	BulletFactory() {}
};