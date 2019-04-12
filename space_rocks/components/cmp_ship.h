#pragma once

#include "ecm.h"
#include "cmp_physics.h"

class ShipComponent : public Component {

public:
	ShipComponent() = delete;
	explicit ShipComponent(Entity* d, const float speed, const float angularSpeed, const float reload);

	void render() override { }
	void update(double dt) override;
	void thrust(double dt);
	void rotate(bool right);
	void shoot();

	~ShipComponent() override = default;

protected:
	float _speed;
	float _angularSpeed;
	float _reload;
	float _time;
	Entity* _bullet;

	std::shared_ptr<PhysicsComponent> _physicsComponent;
	std::shared_ptr<SpriteComponent> _thrusterSpriteComponent;
};