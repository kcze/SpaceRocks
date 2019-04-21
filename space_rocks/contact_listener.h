#pragma once

#include "Box2D/Dynamics/b2WorldCallbacks.h"
#include "ecm.h"
#include "game.h"
#include "components/cmp_destructible.h"
#include "components/cmp_bullet.h"
#include "components/cmp_player.h"
#include "game.h"
#include "Box2D/Box2D.h"

#include <random>

class MyContactListener : public b2ContactListener {
public:
	MyContactListener() {};
protected:
	void BeginContact(b2Contact* contact);

};
