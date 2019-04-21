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
	void setCoinDrop(float chance, unsigned int value) { _coinChance = chance; _coinValue = value; }
	float getCoinChance() { return _coinChance; }
	int getCoinValue() { return _coinValue; }

	~DestructibleComponent() override = default;

protected:
	float _hp;
	float _maxHp;
	unsigned int _id;
	b2Vec2 _spawnCoords;
	bool _timed;
	bool _immune = false;
	float _immuneTime;
	float _lifetime;
	float _flashTime;
	float _coinChance = 0.0f;
	unsigned int _coinValue = 0.0f;
	std::function<void()> _toCall = NULL;
};