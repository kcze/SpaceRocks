#include "cmp_destructible.h"

DestructibleComponent::DestructibleComponent(Entity* p, const float hp) : Component(p)
{
	// Setting hp values
	_hp = hp;
	_maxHp = hp;
}

//Constructor
DestructibleComponent::DestructibleComponent(Entity* p, const float hp, const unsigned int id) : Component(p)
{
	//Set properties
	_hp = hp;
	_maxHp = hp;
	_id = id;
}

float DestructibleComponent::getHp() const { return _hp; }

float DestructibleComponent::getMaxHp() const { return _maxHp; }

void DestructibleComponent::damage(const float hp)
{
	if (hp > 0.0f)
		_hp -= hp;
	if (_hp <= 0.0f)
	{
		//todo should spawn particles/other entities
		_parent->setAlive(false);
		_parent->setVisible(false);
		_parent->setForDelete();
	}
}

void DestructibleComponent::repair(const float hp)
{
	if (hp > 0.0f)
		_hp += hp;
	if (_hp > _maxHp)
		_hp = _maxHp;
}