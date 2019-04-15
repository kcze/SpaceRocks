#include "cmp_bullet.h"
using namespace std;
using namespace sf;

void BulletComponent::update(double dt) {
	//Check for old age
	_lifetime -= dt;
	if (_lifetime <= 0.f) {
		_parent->setForDelete();
	}
}

BulletComponent::BulletComponent(Entity* p, float lifetime)
    : Component(p), _lifetime(lifetime) {}
