#include "cmp_destructible.h"
#include <random>

//Constructor
DestructibleComponent::DestructibleComponent(Entity* p, const float hp, const unsigned int id, const float lifeTime) : Component(p)
{
	//Set properties
	_hp = hp;
	_maxHp = hp;
	_id = id;
	_timed = lifeTime == 0.0f ?  0 : 1;
	_lifetime = lifeTime;
}

//Update
void DestructibleComponent::update(double dt) {
	//Check call list
	if(_toCall)
	{
		(_toCall)();
		_toCall = NULL;
	}

	//Check for old age death if applicable
	if (_timed)
	{
		_lifetime -= dt;
		if (_lifetime <= 0.f) {
			_parent->setForDelete();
		}
	}

	//Check asteroid drifted offscreen (or explosion occured offscreen
	if (sf::length(_parent->getPosition() - sf::Vector2f(GAMEX / 2, GAMEY / 2)) > 805.0f)
	{
		//If particle (Check first as particle doesn't have fixture.)
		if (_parent->getComponents<DestructibleComponent>()[0]->getHp() == FLT_MIN)
			_parent->setForDelete();

		else if (_parent->getComponents<PhysicsComponent>()[0]->getFixture()->GetFilterData().categoryBits == ASTEROIDS)
			_parent->setForDelete();
	}

	//Decrement and unset immunity
	if (_immune)
	{
		_flashTime += dt;
		_immuneTime -= dt;

		//Flash
		if (_flashTime > 1.0f / 6.0f)
		{
			_parent->setVisible(!_parent->isVisible());
			_flashTime = 0.0f;
		}

		//Check if immunity expired
		if (_immuneTime <= 0.0f)
		{
			_parent->setVisible(true);
			_immune = false;
		}
	}

	//Destroied
	if (_hp <= 0.0f)
	{
		//Spawn impact fragments
		spawnFragments(_parent->getPosition());
		//Set for deletion
		_parent->setForDelete();
	}
}


//Get  the HP of this destructible
float DestructibleComponent::getHp() const { return _hp; }

//Get the maximum HP of this destructible
float DestructibleComponent::getMaxHp() const { return _maxHp; }

//Damage this destructible, decreasing its HP by the given value
void DestructibleComponent::damage(const float hp)
{
	//Take damage if not immumne
	if (!_immune)
	{
		//damage
		_hp -= hp;
		
		//if player, set immune
		if (_parent->getComponents<PhysicsComponent>()[0]->getFixture()->GetFilterData().categoryBits == PLAYER_SHIP)
		{
			_immune = true;
			_immuneTime = 1.0f;
			_flashTime = 0.0f;
			_parent->setVisible(false);
		}
	}
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
void DestructibleComponent::spawnFragments(const sf::Vector2f coords) 
{
	switch (_id)
	{
		//0: Bullet (Any)
		case 0:
			//Spawn bullet particles for all bullet impacts, regardless if they kill
			particleBurst(coords, 5, 35.0f);
			//TODO: vary depending on bullet type
			audioManager.playSound("bullet_impact_light");
			break;
		//1: Player
		case 1:
			particleBurst(coords, 50, 100.0f);
			audioManager.playSound("player_death");
			gameScene.playerDeath();
			
			break;
		//2: Enemy (Any)
		case 2:
			audioManager.playSound("enemy_death");
			particleBurst(coords, 20, 100.0f);
			break;
		//3-10: Reserved for expansion
		
		//11+: Asteroids
		//11: Asteroid 1, Size 1
		case 11:
			audioManager.playSound("asteroid_broken");
			particleBurst(coords, 5, 100.0f);
			AsteroidFactory::makeAsteroid(121, coords);
			AsteroidFactory::makeAsteroid(122, coords);
			AsteroidFactory::makeAsteroid(123, coords);
			break;
		//121: Asteroid 1, Size 2, No. 1
		case 121:
			audioManager.playSound("asteroid_broken");
			particleBurst(coords, 5, 100.0f);
			AsteroidFactory::makeAsteroid(1311, coords);
			AsteroidFactory::makeAsteroid(1312, coords);
			break;
		//122: Asteroid 1, Size 2, No. 2
		case 122:
			audioManager.playSound("asteroid_broken");
			particleBurst(coords, 5, 100.0f);
			AsteroidFactory::makeAsteroid(1321, coords);
			AsteroidFactory::makeAsteroid(1322, coords);
			break;
		//131: Asteroid 1, Size 2, No. 3
		case 123:
			audioManager.playSound("asteroid_broken");
			particleBurst(coords, 5, 100.0f);
			AsteroidFactory::makeAsteroid(1331, coords);
			AsteroidFactory::makeAsteroid(1332, coords);
			break;
		default:
			std::cout << "Trying to spawn fragments that don't exist." << std::endl;
	}
}


//TODO: Add lifetime as argument
//Generates a particle burst at the given coords with the given properties
void DestructibleComponent::particleBurst(const sf::Vector2f coords, unsigned int noParticles, float magnitude)
{
	//random
	std::default_random_engine randomGenerator((int)time(NULL));
	std::uniform_real_distribution<float> dF(-1.0f, 1.0f);
	std::uniform_real_distribution<float> dFV(0.5f, 1.0f);
	std::uniform_int_distribution<int> dI(1, 4);

	for (unsigned int i = 0; i < noParticles; i++)
	{
		auto p = ParticleFactory::makeParticle(dI(randomGenerator));
		p->getComponents<PhysicsComponent>()[0]->teleport(coords);

		// Velocity
		//rand gen
		float rx = dF(randomGenerator);
		float ry = dF(randomGenerator);
		float rv = dFV(randomGenerator);
		//get normalised direction from random values
		sf::Vector2f dir = sf::Vector2f(rx, ry);
		dir = sf::normalize<float>(dir);
		p->getComponents<PhysicsComponent>()[0]->setVelocity(dir * rv * magnitude);
		p->getComponents<PhysicsComponent>()[0]->setAngularVelocity(rv * magnitude * 0.75f);
	}
}

//Adds a method call to the call list, which will be called next tick of Update
void DestructibleComponent::setToCall(std::function<void()> call){ _toCall = call; }
