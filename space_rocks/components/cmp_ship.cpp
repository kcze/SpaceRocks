#include "cmp_ship.h"

ShipComponent::ShipComponent(Entity* p, const float speed, const float angularSpeed, const float reload) : Component(p)
{
	_speed = speed;
	_angularSpeed = angularSpeed;
	_reload = reload;
	_time = 0.0f;
	//_bullet = bullet;
	_physicsComponent = _parent->getComponents<PhysicsComponent>()[0];
	_thrusterSpriteComponent = _parent->getComponents<SpriteComponent>()[0];
	_thrusterSpriteComponent->setDraw(false);
	_physicsComponent->setLinearDampening(3.0f);
	_physicsComponent->setAngularDampening(80.0f);
}

ShipComponent::~ShipComponent() {
	_physicsComponent.reset();
	_thrusterSpriteComponent.reset();
}

void ShipComponent::setBullet(float damage, unsigned int id) {_bullet = { damage, id }; }

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
	if (_time > 0.0f)
		return;

	//Play one of two light weapon shots
	std::default_random_engine r((int)time(NULL));
	std::uniform_int_distribution<int> dI(0, 1);
	if(dI(r))
		audioManager.playSound("gun_light_1");
	else
		audioManager.playSound("gun_light_2");

	auto bullet = BulletFactory::makeBullet(_bullet);
	auto physics = bullet->getComponents<PhysicsComponent>()[0];
	physics->teleport(_parent->getPosition());
	physics->setAngle(_physicsComponent->getFixture()->GetBody()->GetAngle());
	physics->impulseRelative(sf::Vector2f(0.0f, -100.0f));
	_time = _reload;
}

void ShipComponent::update(double dt)
{
	_thrusterSpriteComponent->setDraw(false);

	if (_time > 0.0f)
		_time -= dt;
}
