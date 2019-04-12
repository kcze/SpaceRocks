#include "bullet_factory.h"
#include "ecm.h"
#include "engine.h"
#include "game.h"
#include "system_resources.h"
#include "components\cmp_sprite.h"
#include "components\cmp_physics.h"
#include <string>

std::shared_ptr<Entity> BulletFactory::makeBullet()
{
	std::shared_ptr<Entity> entity = gameScene.makeEntity();

	// Sprite
	auto sprite = entity->addComponent<SpriteComponent>();
	sprite->setTexure(Resources::load<sf::Texture>("projectiles.png"));
	sprite->setTextureRect(sf::IntRect(32, 384, 128, 128));
	sprite->SetAnchor(sf::Vector2f(0.5f, 0.5f));

	// Physics
	entity->addComponent<PhysicsComponent>(true, sf::Vector2f(16.0f, 16.0f));

	return entity;
}