#include "ship_factory.h"

std::map < unsigned int, ObjectData > ShipFactory::_objectData =
{
	//Player
	{1,
		{
			{
				{0.0f * PSI8, 4.0f * PSI8},
				{-2.0f * PSI8, -2.0f * PSI8},
				{2.0f * PSI8, 2.0f * PSI8}
			},
			{
				Resources::load<sf::Texture>("player.png")
			},
			{
				sf::IntRect(0, 0, 128, 128)
			}
		}
	},

	//Enemy 1
	{2,
		{
			{
				{0.0f * PSI8, 3.0f * PSI8},
				{-2.0f * PSI8, 1.0f * PSI8},
				{-4.0f * PSI8, -4.0f * PSI8},				
				{4.0f * PSI8, -4.0f * PSI8},
				{2.0f * PSI8, 1.0f * PSI8}
			},
			{
				Resources::load<sf::Texture>("enemies.png")
			},
			{
				sf::IntRect(0, 0, 128, 128)
			}
		}
	},
	//Enemy 2
	{3,
		{
			{
				{0.0f * PSI8, 5.0f * PSI8},
				{-3.0f * PSI8, 1.0f * PSI8},
				{-4.0f * PSI8, -4.0f * PSI8},
				{4.0f * PSI8, -4.0f * PSI8},
				{3.0f * PSI8, 1.0f * PSI8}
			},
			{
				Resources::load<sf::Texture>("enemies.png")
			},
			{
				sf::IntRect(128, 0, 128, 128)
			}
		}
	},
	//Enemy 3
	{4,
		{
			{
				{-4.0f * PSI8, 5.0f * PSI8},
				{5.0f * PSI8, 0.0f * PSI8},
				{4.0f * PSI8, -4.0f * PSI8},
				{4.0f * PSI8, -4.0f * PSI8},
				{5.0f * PSI8, 0.0f * PSI8},
				{4.0f * PSI8, 5.0f * PSI8}
			},
			{
				Resources::load<sf::Texture>("enemies.png")
			},
			{
				sf::IntRect(256, 0, 128, 128)
			}
		}
	},
	//Enemy 4
	{5,
		{
			{
				{-2.0f * PSI8, 5.0f * PSI8},
				{-5.0f * PSI8, 2.0f * PSI8},
				{-4.0f * PSI8, -4.0f * PSI8},
				{4.0f * PSI8, -4.0f * PSI8},
				{5.0f * PSI8, 2.0f * PSI8},
				{2.0f * PSI8, 5.0f * PSI8}
			},
			{
				Resources::load<sf::Texture>("enemies.png")
			},
			{
				sf::IntRect(384, 0, 128, 128)
			}
		}
	}
};

std::shared_ptr<Entity> ShipFactory::makePlayer()
{
	//Make Generic Ship
	auto player = makeShip();

	//Player Component
	{
		player->addComponent<PlayerComponent>(1);
	}

	//Physics
	{
		//Create fixturedef and shape
		b2FixtureDef fixtureDef;
		fixtureDef.filter.categoryBits = PLAYER_SHIP;
		fixtureDef.filter.maskBits = EDGE | ENEMY_BULLET | ENEMY_SHIP | ASTEROIDS;
		b2PolygonShape Shape;

		//Assign collision vertices to shape
		Shape.Set(&_objectData[1]._coords.front(), _objectData[1]._coords.size());
		//Assign shape to fixtureDef
		fixtureDef.shape = &Shape;
		//Assign fixtureDef to physics component
		player->getComponents<PhysicsComponent>()[0]->setFixtureDef(fixtureDef);
		player->getComponents<PhysicsComponent>()[0]->setLinearDampening(0.1f);
	}

	//Destructible
	{
		//ID 1, 5hp
		player->addComponent<DestructibleComponent>(5.0f, 1);
	}

	//Sprite
	{
		auto sprite = player->addComponent<SpriteComponent>();
		sprite->setTexure(_objectData[1]._tex);
	}

	return player;
}

//Make Enemy ship.
//Vaild IDs: 2 through 5 inclusive
std::shared_ptr<Entity> ShipFactory::makeEnemy(unsigned int type)
{
	auto enemy = makeShip();

	//Physics
	{
		//Create fixturedef and shape
		b2FixtureDef fixtureDef;
		fixtureDef.filter.categoryBits = ENEMY_SHIP;
		fixtureDef.filter.maskBits = PLAYER_SHIP | PLAYER_BULLET | ENEMY_SHIP | ASTEROIDS;
		b2PolygonShape Shape;

		//Assign collision vertices to shape
		Shape.Set(&_objectData[type]._coords.front(), _objectData[type]._coords.size());
		//Assign shape to fixtureDef
		fixtureDef.shape = &Shape;
		//Assign fixtureDef to physics component
		enemy->getComponents<PhysicsComponent>()[0]->setFixtureDef(fixtureDef);
		enemy->getComponents<PhysicsComponent>()[0]->setLinearDampening(0.1f);			//<-- TODO: SET THIS WHEN DOING AI
	}

	//Destructible
	{
		//HP governed by ID, so ID 2 = 1hp, ID 3 = 2 hp, etc.
		enemy->addComponent<DestructibleComponent>(type - 1.0f, 2);
	}

	//Sprite
	{
		auto sprite = enemy->addComponent<SpriteComponent>();
		sprite->setTextureRect(_objectData[type]._texRect);
		sprite->setTexure(_objectData[type]._tex);
	}

	return enemy;
}

std::shared_ptr<Entity> ShipFactory::makeShip()
{
	//Make entity
	std::shared_ptr<Entity> entity = gameScene.makeEntity();

	// Thruster sprite to all ships
	auto sprite = entity->addComponent<SpriteComponent>();
	sprite->setTexure(Resources::load<sf::Texture>("thrust.png"));

	//Add components
	entity->addComponent<PhysicsComponent>(true, sf::Vector2f(192.0f, 192.0f));
	entity->addComponent<ShipComponent>(20.0f, 3.0f, 0.5f);

	return entity;
}