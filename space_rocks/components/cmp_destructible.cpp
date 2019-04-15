#include "cmp_destructible.h"
#include "..\asteroid_factory.h"

//Contact Listener
class ContactListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact)
	{
		b2Filter filterA = contact->GetFixtureA()->GetFilterData();
		b2Filter filterB = contact->GetFixtureB()->GetFilterData();
		const b2Vec2 posA = contact->GetFixtureA()->GetBody()->GetPosition();
		const b2Vec2 posB = contact->GetFixtureB()->GetBody()->GetPosition();
		contact->GetFixtureB()->GetBody();


		//Bullet collisions
		if (filterA.groupIndex == 1)
		{
			spawnFragments(posA);
		}
	}
};

//Constructor
DestructibleComponent::DestructibleComponent(Entity* p, const float hp, const unsigned int id) : Component(p)
{
	//Set properties
	_hp = hp;
	_maxHp = hp;
	_id = id;
}

//Update
void DestructibleComponent::update(double dt) {}

//Get  the HP of this destructible
float DestructibleComponent::getHp() const { return _hp; }

//Get the maximum HP of this destructible
float DestructibleComponent::getMaxHp() const { return _maxHp; }

//Damage this destructible, decreasing its HP by the given value
void DestructibleComponent::damage(const float hp, const b2Vec2 coords)
{
	//Take damage
	_hp -= hp;

	//Still alive
	//if (hp > 0.0f)
	//{
	//}
	
	//Destroied
	if (_hp <= 0.0f)
	{
		_parent->setAlive(false);
		_parent->setVisible(false);
		_parent->setForDelete();
	}

	//Spawn impact fragments
	spawnFragments(coords);
}

//Repair this destructible, increasing its HP by the given value
void DestructibleComponent::repair(const float hp)
{
	if (hp > 0.0f)
		_hp += hp;
	if (_hp > _maxHp)
		_hp = _maxHp;
}

//Spawn the fragments relevent to the type of collision at the given coords
void DestructibleComponent::spawnFragments(const b2Vec2 coords) 
{
	switch (_id)
	{
		//0: Bullet (Any)
		case 0:
			//TODO: Spawn bullet particles for all bullet impacts, regardless if they kill
			break;
		//1: Player
		case 1:
			//TODO: Player death explosion/particles
			break;
		//2: Enemy (Any)
		case 2:
			//TODO: Enemy death explosion/particles
			break;
		//3-10: Reserved for expansion
		
		//11+: Asteroids
		//11: Asteroid 1, Size 1
		case 11:
			AsteroidFactory::makeAsteroid(121);
			AsteroidFactory::makeAsteroid(122);
			AsteroidFactory::makeAsteroid(123);
			break;
		//121: Asteroid 1, Size 2, No. 1
		case 121:
			AsteroidFactory::makeAsteroid(1311);
			AsteroidFactory::makeAsteroid(1312);
			break;
		//122: Asteroid 1, Size 2, No. 2
		case 122:
			AsteroidFactory::makeAsteroid(1321);
			AsteroidFactory::makeAsteroid(1322);
			break;
		//131: Asteroid 1, Size 2, No. 3
		case 123:
			AsteroidFactory::makeAsteroid(1331);
			AsteroidFactory::makeAsteroid(1332);
			break;
	}
}
