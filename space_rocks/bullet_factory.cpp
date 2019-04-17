#include "bullet_factory.h"

//Key is ColRow starting top left: 11
std::map < unsigned int, ObjectData > BulletFactory::_objectData =
{
	//1,2
	{12,
		{
			{
				{0.0f * PSI4, 1.0f * PSI4},
				{-1.0f * PSI4, 0.0f * PSI4},
				{0.0f * PSI4, -1.0f * PSI4},
				{1.0f * PSI4, 0.0f * PSI4}
			},
			{
				Resources::load<sf::Texture>("projectiles.png")
			},
			{
				sf::IntRect(0, 64, 64, 64)
			}
		}
	},

	//2,2
	{22,
		{
			{
				{0.0f * PSI4, 2.0f * PSI4},
				{-2.0f * PSI4, 0.0f * PSI4},
				{0.0f * PSI4, -2.0f * PSI4},
				{2.0f * PSI4, 0.0f * PSI4}
			},
			{
				Resources::load<sf::Texture>("projectiles.png")
			},
			{
				sf::IntRect(64, 64, 64, 64)
			}
		}
	},

	//3,2
	{32,
		{
			{
				{0.0f * PSI4, 3.0f * PSI4},
				{-3.0f * PSI4, 0.0f * PSI4},
				{0.0f * PSI4, -3.0f * PSI4},
				{3.0f * PSI4, 0.0f * PSI4}
			},
			{
				Resources::load<sf::Texture>("projectiles.png")
			},
			{
				sf::IntRect(128, 64, 64, 64)
			}
		}
	},

	//1,3
	{13,
		{
			{
				{0.0f * PSI4, 2.0f * PSI4},
				{-1.0f * PSI4, 1.0f * PSI4},
				{-1.0f * PSI4, -1.0f * PSI4},
				{0.0f * PSI4, -2.0f * PSI4},
				{1.0f * PSI4, -1.0f * PSI4},
				{1.0f * PSI4, 1.0f * PSI4}
			},
			{
				Resources::load<sf::Texture>("projectiles.png")
			},
			{
				sf::IntRect(0, 128, 64, 64)
			}
		}
	},

	//2,3
	{23,
		{
			{
				{0.0f * PSI4, 3.0f * PSI4},
				{-1.0f * PSI4, 1.0f * PSI4},
				{-1.0f * PSI4, -1.0f * PSI4},
				{0.0f * PSI4, -3.0f * PSI4},
				{1.0f * PSI4, -1.0f * PSI4},
				{1.0f * PSI4, 1.0f * PSI4}
			},
			{
				Resources::load<sf::Texture>("projectiles.png")
			},
			{
				sf::IntRect(64, 128, 64, 64)
			}
		}
	},

	//3,3
	{33,
		{
			{
				{0.0f * PSI4, 4.0f * PSI4},
				{-2.0f * PSI4, 2.0f * PSI4},
				{-2.0f * PSI4, -2.0f * PSI4},
				{0.0f * PSI4, -4.0f * PSI4},
				{2.0f * PSI4, -2.0f * PSI4},
				{2.0f * PSI4, 2.0f * PSI4}
			},
			{
				Resources::load<sf::Texture>("projectiles.png")
			},
			{
				sf::IntRect(128, 128, 64, 64)
			}
		}
	},

	//Player Bullets:

	//1,4
	{14,
		{
			{
				{0.0f * PSI4, 2.0f * PSI4},
				{-1.0f * PSI4, 0.0f * PSI4},
				{0.0f * PSI4, -4.0f * PSI4},
				{1.0f * PSI4, 0.0f * PSI4}
			},
			{
				Resources::load<sf::Texture>("projectiles.png")
			},
			{
				sf::IntRect(0, 192, 64, 64)
			}
		}
	},

	//2,4
	{24,
		{
			{
				{0.0f * PSI4, 2.0f * PSI4},
				{-2.0f * PSI4, 0.0f * PSI4},
				{0.0f * PSI4, -4.0f * PSI4},
				{2.0f * PSI4, 0.0f * PSI4}
			},
			{
				Resources::load<sf::Texture>("projectiles.png")
			},
			{
				sf::IntRect(64, 192, 64, 64)
			}
		}
	},

	//3,4
	{ 24,
		{
			{
				{0.0f * PSI4, 2.0f * PSI4},
				{-2.0f * PSI4, 0.0f * PSI4},
				{0.0f * PSI4, -6.0f * PSI4},
				{2.0f * PSI4, 0.0f * PSI4}
			},
			{
				Resources::load<sf::Texture>("projectiles.png")
			},
			{
				sf::IntRect(128, 192, 64, 64)
			}
		}
	}
};

//Make a bullet of the corresponding type 
//i.e: 14 = Default Player Bullet
std::shared_ptr<Entity> BulletFactory::makeBullet(Bullet b)
{

	//Make entity
	std::shared_ptr<Entity> bullet = gameScene.makeEntity();

	// Physics
	{
		auto phys = bullet->addComponent<PhysicsComponent>(true, sf::Vector2f(16.0f, 16.0f));
		//Collider
		//Create fixturedef and shape
		b2FixtureDef fixtureDef;
		fixtureDef.filter.groupIndex = 1;
		if (b._id == 14 || b._id == 24 || b._id == 34)
		{
			fixtureDef.filter.categoryBits = PLAYER_BULLET;
			fixtureDef.filter.maskBits = ENEMY_BULLET | ENEMY_SHIP | ASTEROIDS;
		}
		else
		{
			fixtureDef.filter.categoryBits = ENEMY_BULLET;
			fixtureDef.filter.maskBits = PLAYER_BULLET | PLAYER_SHIP | ASTEROIDS;
		}
		b2PolygonShape shape;
		//Set collider to sensor
		fixtureDef.isSensor = true;
		//Assign vertices to shape
		shape.Set(&_objectData[b._id]._coords.front(), _objectData[b._id]._coords.size());
		//Assign shape to fixtureDef
		fixtureDef.shape = &shape;
		//Assign fixtureDef to physics component
		phys->setFixtureDef(fixtureDef);
	}

	// Sprite
	{
		auto sprite = bullet->addComponent<SpriteComponent>();
		sprite->setTexure(_objectData[b._id]._tex);
		sprite->setTextureRect(_objectData[b._id]._texRect);
		sprite->setAnchor(sf::Vector2f(0.5f, 0.5f));
	}

	//Destructible
	{
		auto des = bullet->addComponent<DestructibleComponent>(1.0f, 0, 5.0f);
	}

	//Bullet Component
	{
		//5 seconds lifetime
		auto des = bullet->addComponent<BulletComponent>(b._damage);
	}
	return bullet;
}