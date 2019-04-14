#include "asteroid_factory.h"

const float  AsteroidFactory::PSI16 = Physics::physics_scale_inv * 16.0f;

std::map < unsigned int, std::vector<b2Vec2 >> AsteroidFactory::_coords = {
	
	// Asteroid 1
	//11
	{ 11,
		{
			{0.0f * PSI16, 6.0f * PSI16},
			{-5.0f * PSI16, 4.0f * PSI16},
			{-6.0f * PSI16, -1.0f * PSI16},
			{-5.0f * PSI16, -4.0f * PSI16},
			{0.0f * PSI16, -6.0f * PSI16},
			{5.0f * PSI16, -4.0f * PSI16},
			{6.0f * PSI16, 0.0f * PSI16},
			{4.0f * PSI16, 4.0f * PSI16}
		}
	},
	//121
	{121,
		{
			{0.0f * PSI16, 6.0f * PSI16},
			{-5.0f * PSI16, 4.0f * PSI16},
			{-6.0f * PSI16, -1.0f * PSI16},
			{0.0f * PSI16, 1.0f * PSI16}
		}
	},
	//122
	{122,
		{
			{0.0f * PSI16, 1.0f * PSI16},
			{-6.0f * PSI16, -1.0f * PSI16},
			{-5.0f * PSI16, -4.0f * PSI16},
			{0.0f * PSI16, -6.0f * PSI16},
			{5.0f * PSI16, -4.0f * PSI16}
		}
	},
	//123
	{123,
		{
			{0.0f * PSI16, 6.0f * PSI16},
			{0.0f * PSI16, 1.0f * PSI16},
			{5.0f * PSI16, -4.0f * PSI16},
			{6.0f * PSI16, 0.0f * PSI16},
			{4.0f * PSI16, 4.0f * PSI16}
		}
	},
	//1311
	{1311,
		{
			{0.0f * PSI16, 1.0f * PSI16},
			{-5.0f * PSI16, 4.0f * PSI16},
			{-6.0f * PSI16, -1.0f * PSI16}
		}
	},
	//1312
	{1312,
		{
			{0.0f * PSI16, 6.0f * PSI16},
			{-5.0f * PSI16, 4.0f * PSI16},
			{0.0f * PSI16, 1.0f * PSI16}
		}
	},
	//1321
	{1321,
		{
			{0.0f * PSI16, 1.0f * PSI16},
			{-6.0f * PSI16, -1.0f * PSI16},
			{-5.0f * PSI16, -4.0f * PSI16},
			{0.0f * PSI16, -6.0f * PSI16}
		}
	},
	//1322
	{1322,
		{
			{0.0f * PSI16, 1.0f * PSI16},
			{0.0f * PSI16, -6.0f * PSI16},
			{5.0f * PSI16, -4.0f * PSI16}
		}
	},
	//1331
	{1331,
		{
			{0.0f * PSI16, 1.0f * PSI16},
			{5.0f * PSI16, -4.0f * PSI16},
			{6.0f * PSI16, 0.0f * PSI16},
			{5.0f * PSI16, 2.0f * PSI16}
		}
	}, 
	//1332
	{1332,
		{
			{0.0f * PSI16, 6.0f * PSI16},
			{0.0f * PSI16, 1.0f * PSI16},
			{5.0f * PSI16, 2.0f * PSI16},
			{4.0f * PSI16, 4.0f * PSI16}
		}
	}
};


std::shared_ptr<Entity> AsteroidFactory::makeAsteroid(unsigned int id) 
{
	switch (id)
	{
	case 11:
		//Make entity
		auto asteroid = gameScene.makeEntity();
		
		// - Physics -
		auto phys = asteroid->addComponent<PhysicsComponent>(true, sf::Vector2f(10.0f, 10.0f));
		//Collider
		//Create fixturedef and shape
		b2FixtureDef fixtureDef;
		b2PolygonShape shape;
		
		//Assign vertices to shape
		shape.Set(&_coords[11].front(), _coords[11].size());
		//Assign shape to fixtureDef
		fixtureDef.shape = &shape;
		//Assign fixtureDef to physics component
		phys->setFixtureDef(fixtureDef);

		// - Sprite -
		auto spr = asteroid->addComponent<SpriteComponent>();
		spr->setTextureRect(sf::IntRect(0, 0, 256, 256));
		spr->setTexure(Resources::load<sf::Texture>("asteroid-1.png"));
		
		return asteroid;
		break;
	}

	return NULL;
}