#pragma once

#include "ecm.h"
#include "Box2D/Box2D.h"
#include "..\asteroid_factory.h"
#include "..\particle_factory.h"
#include "time.h"

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
	void particleBurst(const sf::Vector2f coords, unsigned int noParticles, float magnitude);
	void setToCall(std::function<void()>);
	
	~DestructibleComponent() override = default;

protected:
	float _hp;
	float _maxHp;
	unsigned int _id;
	b2Vec2 _spawnCoords;
	bool _timed;
	float _lifetime;
	std::function<void()> _toCall = NULL;
};