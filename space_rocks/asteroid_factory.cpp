#include "asteroid_factory.h"



const float  AsteroidFactory::PSI16 = Physics::physics_scale_inv * 16.0f;

std::map < unsigned int, ObjectData> AsteroidFactory::_objectData = 
{	
	//11: Asteroid 1, Size 1
	{11,
		{
			{
				{0.0f * PSI16, 6.0f * PSI16},
				{-5.0f * PSI16, 4.0f * PSI16},
				{-6.0f * PSI16, -1.0f * PSI16},
				{-5.0f * PSI16, -4.0f * PSI16},
				{0.0f * PSI16, -6.0f * PSI16},
				{5.0f * PSI16, -4.0f * PSI16},
				{6.0f * PSI16, 0.0f * PSI16},
				{4.0f * PSI16, 4.0f * PSI16}
			},
			{
				Resources::load<sf::Texture>("asteroid-1.png")
			},
			{
				sf::IntRect(0, 0, 256, 256)
			}
		}
	},

	//121
	{121,
		{
			{
				{0.0f * PSI16, 6.0f * PSI16},
				{-5.0f * PSI16, 4.0f * PSI16},
				{-6.0f * PSI16, -1.0f * PSI16},
				{0.0f * PSI16, 1.0f * PSI16}
			},
			{
				Resources::load<sf::Texture>("asteroid-1.png")
			},
			{
				sf::IntRect(256, 0, 256, 256)
			},
		}
	},
	//122
	{122,
		{
			{
				{0.0f * PSI16, 1.0f * PSI16},
				{-6.0f * PSI16, -1.0f * PSI16},
				{-5.0f * PSI16, -4.0f * PSI16},
				{0.0f * PSI16, -6.0f * PSI16},
				{5.0f * PSI16, -4.0f * PSI16}
			},
			{
				Resources::load<sf::Texture>("asteroid-1.png")
			},
			{
				sf::IntRect(512, 0, 256, 256)
			},
		}
	},	
	//123
	{123,
		{
			{
				{0.0f * PSI16, 6.0f * PSI16},
				{0.0f * PSI16, 1.0f * PSI16},
				{5.0f * PSI16, -4.0f * PSI16},
				{6.0f * PSI16, 0.0f * PSI16},
				{4.0f * PSI16, 4.0f * PSI16}
			},
			{
				Resources::load<sf::Texture>("asteroid-1.png")
			},
			{
				sf::IntRect(768, 0, 256, 256)
			},
		}
	},
	//1311
	{1311,
		{
			{
				{0.0f * PSI16, 1.0f * PSI16},
				{-5.0f * PSI16, 4.0f * PSI16},
				{-6.0f * PSI16, -1.0f * PSI16}
			},
			{
				Resources::load<sf::Texture>("asteroid-1.png")
			},
			{
				sf::IntRect(0, 256, 256, 256)
			},
		}
	},
	//1312
	{1312,
		{
			{
				{0.0f * PSI16, 6.0f * PSI16},
				{-5.0f * PSI16, 4.0f * PSI16},
				{0.0f * PSI16, 1.0f * PSI16}
			},
			{
				Resources::load<sf::Texture>("asteroid-1.png")
			},
			{
				sf::IntRect(256, 256, 256, 256)
			},
		}
	},
	//1321
	{1321,
		{
			{
				{0.0f * PSI16, 1.0f * PSI16},
				{-6.0f * PSI16, -1.0f * PSI16},
				{-5.0f * PSI16, -4.0f * PSI16},
				{0.0f * PSI16, -6.0f * PSI16}
			},
			{
				Resources::load<sf::Texture>("asteroid-1.png")
			},
			{
				sf::IntRect(0, 512, 256, 256)
			},
		}
	},
	//1322
	{1322,
		{
			{
				{0.0f * PSI16, 1.0f * PSI16},
				{0.0f * PSI16, -6.0f * PSI16},
				{5.0f * PSI16, -4.0f * PSI16}
			},
			{
				Resources::load<sf::Texture>("asteroid-1.png")
			},
			{
				sf::IntRect(256, 512, 256, 256)
			},
		}
	},
	//1331
	{1331,
		{
			{
				{0.0f * PSI16, 1.0f * PSI16},
				{5.0f * PSI16, -4.0f * PSI16},
				{6.0f * PSI16, 0.0f * PSI16},
				{5.0f * PSI16, 2.0f * PSI16}
			},
			{
				Resources::load<sf::Texture>("asteroid-1.png")
			},
			{
				sf::IntRect(0, 768, 256, 256)
			},
		}
	},
	//1332
	{1332,
		{
			{
				{0.0f * PSI16, 6.0f * PSI16},
				{0.0f * PSI16, 1.0f * PSI16},
				{5.0f * PSI16, 2.0f * PSI16},
				{4.0f * PSI16, 4.0f * PSI16}
			},
			{
				Resources::load<sf::Texture>("asteroid-1.png")
			},
			{
				sf::IntRect(256, 768, 256, 256)
			},
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
		
		// Physics
		{
			auto phys = asteroid->addComponent<PhysicsComponent>(true, sf::Vector2f(10.0f, 10.0f));
			//Collider
			//Create fixturedef and shape
			b2FixtureDef fixtureDef;
			fixtureDef.filter.categoryBits = ASTEROIDS;
			fixtureDef.filter.maskBits = PLAYER_BULLET | PLAYER_SHIP | ENEMY_BULLET | ENEMY_SHIP | ASTEROIDS;
			b2PolygonShape shape;
			//Assign vertices to shape
			shape.Set(&_objectData[11]._coords.front(), _objectData[11]._coords.size());
			//Assign shape to fixtureDef
			fixtureDef.shape = &shape;
			//Assign fixtureDef to physics component
			phys->setFixtureDef(fixtureDef);
		}

		// Sprite
		{
			auto spr = asteroid->addComponent<SpriteComponent>();
			spr->setTextureRect(_objectData[11]._texRect);
			spr->setTexure(_objectData[11]._tex);
		}

		// Destructible
		{
			//3 hp
			auto des = asteroid->addComponent<DestructibleComponent>(3.0f, 11);
		}

		return asteroid;
		break;
	}

	std::cout << "Invalid ID" << std::endl;
	return NULL;
}