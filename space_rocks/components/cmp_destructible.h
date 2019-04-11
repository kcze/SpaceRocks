#pragma once

#include "ecm.h"

class DestructibleComponent : public Component {

public:
	DestructibleComponent() = delete;
	explicit DestructibleComponent(Entity* p, const float hp);

	void render() override { } 
	void update(double dt) override;
	float getHp() const;
	float getMaxHp() const;
	void damage(const float hp);
	void repair(const float hp);

	~DestructibleComponent() override = default;

protected:
	float _hp;
	float _maxHp;
};