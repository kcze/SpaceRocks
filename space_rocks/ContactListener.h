#pragma once

#include "Box2D/Dynamics/b2WorldCallbacks.h"
#include "ecm.h"
#include "game.h"
#include "components/cmp_destructible.h"
#include "components/cmp_bullet.h"
#include "Box2D/Box2D.h"

class myContactListener : public b2ContactListener {
public:
	myContactListener() {};
protected:
	void BeginContact(b2Contact* contact);

};
