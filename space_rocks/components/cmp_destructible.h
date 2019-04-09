#pragma once

#include "ecm.h"

class DestructibleComponent : public Component {
protected:
	float _hp;
	float _maxHp;

public:
	DestructibleComponent(Entity* d, const float hp);

	void update(double dt) override;
	float getHp() const;
	float getMaxHp() const;
	void damage(const float hp);
	void repair(const float hp);

	~DestructibleComponent() override = default;
};