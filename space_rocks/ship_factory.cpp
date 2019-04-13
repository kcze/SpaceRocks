#include "ship_factory.h"
#include "ecm.h"
#include "engine.h"
#include "game.h"
#include "components\cmp_sprite.h"
#include "components\cmp_physics.h"
#include "components\cmp_ship.h"
#include "components\cmp_destructible.h"
#include "components\cmp_player.h"
#include "system_resources.h"
#include "Box2D/Box2D.h"
#include <string>
#include "system_physics.h"


std::shared_ptr<Entity> ShipFactory::makePlayer()
{
	auto player = makeShip();

	player->addComponent<PlayerComponent>(1);
	
	player->get_components<PhysicsComponent>()[0]->setLinearDampening(0.1f);
	
	//Create fixturedef and shape
	b2FixtureDef fixtureDef;
	fixtureDef.filter.categoryBits = PLAYER_SHIP;
	fixtureDef.filter.maskBits = EDGE | ENEMY_BULLET | ENEMY_SHIP | ASTEROIDS;
	b2PolygonShape Shape;
	//Set collision vertices
	b2Vec2 vertices[3];
	float PSI = Physics::physics_scale_inv;
	vertices[0].Set(0.0f * PSI, 55.0f * PSI);
	vertices[1].Set(-38.0f * PSI, -40.0f * PSI);
	vertices[2].Set(38.0f * PSI, -40.0f * PSI);
	unsigned int vertexCount = 3;
	//Assign vertices to shape
	Shape.Set(vertices, vertexCount);
	//Assign shape to fixtureDef
	fixtureDef.shape = &Shape;
	//Assign fixtureDef to physics component
	player->get_components<PhysicsComponent>()[0]->setFixtureDef(fixtureDef);

	//Debug dump
	player->get_components<PhysicsComponent>()[0]->dump();

	return player;
}

std::shared_ptr<Entity> ShipFactory::makeEnemy()
{
	return makeShip();
}

std::shared_ptr<Entity> ShipFactory::makeShip()
{
	std::shared_ptr<Entity> entity = gameScene.makeEntity();

	// Sprite
	auto sprite = entity->addComponent<SpriteComponent>();
	//sprite->setTextureRect(sf::IntRect(0, 0, 256, 256));
	sprite->setTexure(Resources::load<sf::Texture>("player.png"));

	// Thruster sprite
	sprite = entity->addComponent<SpriteComponent>();
	sprite->setTexure(Resources::load<sf::Texture>("thrust.png"));

	// Physics
	entity->addComponent<PhysicsComponent>(true, sf::Vector2f(192.0f, 192.0f));

	// Ship
	entity->addComponent<ShipComponent>(20.0f, 2.0f, 0.5f);

	// Destructible
	entity->addComponent<DestructibleComponent>(100.0f);


	return entity;
}