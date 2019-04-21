#include "asteroid_factory.h"


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


std::shared_ptr<Entity> AsteroidFactory::makeAsteroid(unsigned int id, sf::Vector2f coords)
{
	//Make entity
	auto asteroid = gameScene.makeEntity();
	asteroid->setPosition(coords);

	// Sprite
	{
		auto spr = asteroid->addComponent<SpriteComponent>();
		spr->setTextureRect(_objectData[id]._texRect);
		spr->setTexure(_objectData[id]._tex);
	}

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
		shape.Set(&_objectData[id]._coords.front(), _objectData[id]._coords.size());
		//Assign shape to fixtureDef
		fixtureDef.shape = &shape;
		//Assign fixtureDef to physics component
		phys->setFixtureDef(fixtureDef);
	}

	// Destructible
	{
		std::shared_ptr<DestructibleComponent> des;
		if(id == 11)
			des = asteroid->addComponent<DestructibleComponent>(3.0f, id); //3 hp
		else if (id == 121 || 122 || 123)
			des = asteroid->addComponent<DestructibleComponent>(2.0f, id); //2 hp
		else
			des = asteroid->addComponent<DestructibleComponent>(1.0f, id); //1 hp

		//50% drop chance of 1 coin
		des->setCoinDrop(0.5f, 1);
	}

	return asteroid;
}