#pragma once

#include "ecm.h"
#include "Box2D/Box2D.h"

class DestructibleComponent : public Component {

public:
	DestructibleComponent() = delete;
	explicit DestructibleComponent(Entity* p, const float hp, const unsigned int id, const float lifeTime = 0.0f);

	void render() override { } 
	void update(double dt) override;
	float getHp() const;
	float getMaxHp() const;
	void damage(const float hp);
	void repair(const float hp);
	void spawnFragments(const sf::Vector2f coords);

	~DestructibleComponent() override = default;

protected:
	float _hp;
	float _maxHp;
	unsigned int _id;
	b2Vec2 _spawnCoords;
	bool _timed;
	float _lifetime;
};