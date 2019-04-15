#include "cmp_ship.h"

ShipComponent::ShipComponent(Entity* p, const float speed, const float angularSpeed, const float reload) : Component(p)
{
	_speed = speed;
	_angularSpeed = angularSpeed;
	_reload = reload;
	_time = 0.0f;
	//_bullet = bullet;
	_physicsComponent = _parent->get_components<PhysicsComponent>()[0];
	_thrusterSpriteComponent = _parent->get_components<SpriteComponent>()[0];
	_thrusterSpriteComponent->setDraw(false);
	_physicsComponent->setLinearDampening(3.0f);
	_physicsComponent->setAngularDampening(50.0f);
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
	std::cout << "_time = " << _time << std::endl;
	if (_time > 0.0f)
		return;

	auto bullet = BulletFactory::makeBullet(24);
	auto physics = bullet->get_components<PhysicsComponent>()[0];
	physics->teleport(_parent->getPosition());
	physics->setAngle(_physicsComponent->getFixture()->GetBody()->GetAngle());
	physics->impulseRelative(sf::Vector2f(0.0f, -10.0f));
	_time = _reload;
}

void ShipComponent::update(double dt)
{
	//todo may override thrust() and always be false
	// works because player fires thrust() after this update
	_thrusterSpriteComponent->setDraw(false);

	if (_time > 0.0f)
		_time -= dt;
	else
		_time = _reload;
}
