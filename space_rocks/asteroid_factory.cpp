#include "asteroid_factory.h"

std::map < unsigned int, std::vector<b2Vec2 >> AsteroidFactory::_coords = {
	// 11
	{ 11,
		{
			{0.0f * Physics::physics_scale_inv, 96.0f * Physics::physics_scale_inv},
			{-80.0f * Physics::physics_scale_inv, 64.0f * Physics::physics_scale_inv},
			{-96.0f * Physics::physics_scale_inv, -16.0f * Physics::physics_scale_inv},
			{-80.0f * Physics::physics_scale_inv, -64.0f * Physics::physics_scale_inv},
			{0.0f * Physics::physics_scale_inv, -96.0f * Physics::physics_scale_inv},
			{80.0f * Physics::physics_scale_inv, -64.0f * Physics::physics_scale_inv},
			{96.0f * Physics::physics_scale_inv, 0.0f * Physics::physics_scale_inv},
			{64.0f * Physics::physics_scale_inv, 64.0f * Physics::physics_scale_inv}
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