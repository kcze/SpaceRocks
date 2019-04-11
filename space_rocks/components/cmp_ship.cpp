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
	_physicsComponent->getFixture()->GetBody()->SetLinearDamping(0.01f);
	_physicsComponent->getFixture()->GetBody()->SetAngularDamping(0.01f);
}

void ShipComponent::thrust()
{
	_physicsComponent->setVelocity(sf::Vector2f(0.0f, 1.0f));
}

void ShipComponent::rotate(bool left)
{
	_physicsComponent->setAngularVelocity(left ? _angularSpeed : -_angularSpeed);
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
