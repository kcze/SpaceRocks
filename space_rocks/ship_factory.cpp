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
#include <string>

std::shared_ptr<Entity> ShipFactory::makePlayer()
{
	auto player = makeShip();

	player->addComponent<PlayerComponent>(1);
	player->get_components<PhysicsComponent>()[0]->setLinearDampening(0.1f);
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

	// Physics
	entity->addComponent<PhysicsComponent>(true, sf::Vector2f(192.0f, 192.0f));
	// Ship
	entity->addComponent<ShipComponent>(20.0f, 2.0f, 1.0f);
	// Destructible
	entity->addComponent<DestructibleComponent>(100.0f);

	return entity;
}