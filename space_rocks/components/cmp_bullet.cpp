#include "cmp_bullet.h"
using namespace std;
using namespace sf;

void BulletComponent::update(double dt) {

}

BulletComponent::BulletComponent(Entity* p, float damage)
    : Component(p) , _damage(damage){}

float BulletComponent::getDamage() { return _damage; };
