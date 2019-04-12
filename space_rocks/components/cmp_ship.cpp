#include "cmp_ship.h"
#include "maths.h"
#include <Box2D\Dynamics\b2Fixture.h>

ShipComponent::ShipComponent(Entity* p, const float speed, const float angularSpeed, const float reload) : Component(p)
{
	_speed = speed;
	_angularSpeed = angularSpeed;
	_reload = reload;
	//_bullet = bullet;
	_physicsComponent = _parent->get_components<PhysicsComponent>()[0];
	_thrusterSpriteComponent = _parent->get_components<SpriteComponent>()[1];
	_thrusterSpriteComponent->setDraw(false);
	_physicsComponent->getFixture()->GetBody()->SetLinearDamping(3.0f);
	_physicsComponent->getFixture()->GetBody()->SetAngularDamping(5.0f);
}

void ShipComponent::thrust(double dt)
{
	_physicsComponent->impulseRelative(sf::Vector2f(0.0f, -_speed * dt));
	_thrusterSpriteComponent->setDraw(true);
}

void ShipComponent::rotate(bool right)
{
	_physicsComponent->setAngularVelocity(right ? _angularSpeed : -_angularSpeed);
}

void ShipComponent::shoot()
{
	//todo ship shooting
}

void ShipComponent::update(double dt)
{
	//todo may override thrust() and always be false
	// works because player fires thrust() after this update
	_thrusterSpriteComponent->setDraw(false);
}
