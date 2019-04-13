#pragma once

#include "ecm.h"
#include <map>
#include "Box2D/Box2D.h"
#include "system_physics.h"
#include "game.h"
#include "engine.h"
#include "components\cmp_sprite.h"
#include "components\cmp_physics.h"
#include "system_resources.h"



class AsteroidFactory {
public:
	static std::shared_ptr<Entity> makeAsteroid(unsigned int id);

private:
	AsteroidFactory() {}

	std::shared_ptr<sf::Texture> ssAsteroids;

	static std::map<unsigned int, b2Vec2* > _coords;
	//Asteroid 1
	static b2Vec2* _11Coords;
	static b2Vec2* _121Coords;
	static b2Vec2* _122Coords;
	static b2Vec2* _123Coords;
	static b2Vec2* _1311Coords;
	static b2Vec2* _1312Coords;
	static b2Vec2* _1321Coords;
	static b2Vec2* _1322Coords;
	static b2Vec2* _1331Coords;
	static b2Vec2* _1332Coords;

};

