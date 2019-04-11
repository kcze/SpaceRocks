#include "cmp_ship.h"
#include "maths.h"
#include <Box2D\Dynamics\b2Fixture.h>

ShipComponent::ShipComponent(Entity* p, const float speed, const float angularSpeed, const float reload) : Component(p)
{
	// Setting hp values
	_speed = speed;
	_angularSpeed = angularSpeed;
	_reload = reload;
	//_bullet = bullet;
	_physicsComponent = _parent->get_components<PhysicsComponent>()[0];
	_physicsComponent->getFixture()->GetBody()->SetLinearDamping(3.0f);
	_physicsComponent->getFixture()->GetBody()->SetAngularDamping(5.0f);
}

void ShipComponent::thrust(double dt)
{
	_physicsComponent->impulseRelative(sf::Vector2f(0.0f, -_speed * dt));
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
	//todo probably not needed
	//_physicsComponent->dampen(sf::Vector2f(0.9f * dt, 0.9f * dt));
}
