#include "asteroid_factory.h"


//Asteroid 1
static b2Vec2 _11CoordsData[] =
{
	{0.0f * Physics::physics_scale_inv, 96.0f * Physics::physics_scale_inv},
	{-80.0f * Physics::physics_scale_inv, 64.0f * Physics::physics_scale_inv},
	{-96.0f * Physics::physics_scale_inv, -16.0f * Physics::physics_scale_inv},
	{-80.0f * Physics::physics_scale_inv, -64.0f * Physics::physics_scale_inv},
	{0.0f * Physics::physics_scale_inv, -96.0f * Physics::physics_scale_inv},
	{80.0f * Physics::physics_scale_inv, -64.0f * Physics::physics_scale_inv},
	{96.0f * Physics::physics_scale_inv, 0.0f * Physics::physics_scale_inv},
	{64.0f * Physics::physics_scale_inv, 64.0f * Physics::physics_scale_inv}
};

static b2Vec2* _11Coords = _11CoordsData;

std::vector<b2Vec2> _121Coords;
std::vector<b2Vec2> _122Coords;
std::vector<b2Vec2> _123Coords;
std::vector<b2Vec2> _1311Coords;
std::vector<b2Vec2> _1312Coords;
std::vector<b2Vec2> _1321Coords;
std::vector<b2Vec2> _1322Coords;
std::vector<b2Vec2> _1331Coords;
std::vector<b2Vec2> _1332Coords;


std::map<unsigned int, b2Vec2* > _coords =
{
	// Asteroid 1
	//size 1
	{11, _11Coords }

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
		b2PolygonShape Shape;
		//Assign vertices to shape
		Shape.Set(_coords[11], _coords[11]->Length());
		//Assign shape to fixtureDef
		fixtureDef.shape = &Shape;
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