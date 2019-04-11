#pragma once

#include "ecm.h"
#include "cmp_physics.h"

class ShipComponent : public Component {

public:
	ShipComponent() = delete;
	explicit ShipComponent(Entity* d, const float speed, const float angularSpeed, const float reload);

	void render() override { }
	void update(double dt) override;
	void thrust();
	void rotate(bool left);
	void shoot();

	~ShipComponent() override = default;

protected:
	float _speed;
	float _angularSpeed;
	float _reload;
	Entity* _bullet;

	std::shared_ptr<PhysicsComponent> _physicsComponent;
};