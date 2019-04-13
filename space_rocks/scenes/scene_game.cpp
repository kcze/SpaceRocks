#include "scene_game.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_physics.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "../input.h"
#include "system_renderer.h"
#include "maths.h"
#include <stdlib.h>
#include <time.h>
#include "system_resources.h"
#include <random>
#include "..\ship_factory.h"
#include "Box2D/Box2D.h"
#include "system_physics.h"


using namespace std;
using namespace sf;


std::vector<std::shared_ptr<Entity>> asteroids;
std::shared_ptr<sf::Texture> ssAsteroids;
default_random_engine randomGenerator((int)time(NULL));
uniform_real_distribution<float> distrib(-1.0f, 1.0f);

void GameScene::Load() {
	cout << "Game Scene Load \n";
	{
		//Score text
		auto txt = makeEntity();
		auto txtcmp = txt->addComponent<TextComponent>("Score: ");
		txtcmp->SetAnchor(sf::Vector2f(0.0f, 0.5f));
		txt->setPosition(sf::Vector2f(16.0f, 16.0f));
	}

	// Load spritesheets
	ssAsteroids = Resources::load<Texture>("asteroid-1.png");

	// Test ship
	auto player = ShipFactory::makePlayer();
	player->get_components<PhysicsComponent>()[0]->teleport(Vector2f(GAMEX / 2, GAMEY / 2));

	srand(time(NULL));
	setLoaded(true);
}

void GameScene::SpawnAsteroid()
{
	//asteroids.shrink_to_fit(); //TODO: Ensure list is shrunk when asteroid is destroyed...
	
	auto asteroid = makeEntity();
	// Generate random position off screen
	float rx = distrib(randomGenerator);
	float ry = distrib(randomGenerator);
	cout << "rx: " << rx << "  ry: " << ry;
	//get normalised direction from random values
	sf::Vector2f dir = sf::Vector2f(rx, ry);
	dir = sf::normalize<float>(dir);
	//calculate center of screen
	sf::Vector2f center = sf::Vector2f(GAMEX/2, GAMEY/2);
	//Set asteroid starting position
	asteroid->setPosition(center + dir*800.0f);
	
	// Physics
	auto phys = asteroid->addComponent<PhysicsComponent>(true, sf::Vector2f(10.0f, 10.0f));
	//Set velocity back towards center
	//TODO: Random variation to prevent all asteroids heading straight to center.
	phys->setVelocity(sf::Vector2f(dir.x, -dir.y) * -25.0f);
	//Collider
	//Create fixturedef and shape
	b2FixtureDef fixtureDef;
	b2PolygonShape Shape;
	//Set collision vertices
	const unsigned int vertexCount = 8;
	b2Vec2 vertices[vertexCount];
	float PSI = Physics::physics_scale_inv;
	vertices[0].Set(0.0f * PSI, 100.0f * PSI);
	vertices[1].Set(-85.0f * PSI, 66.0f * PSI);
	vertices[2].Set(-100.0f * PSI, -17.0f * PSI);
	vertices[3].Set(-81.0f * PSI, -67.0f * PSI);	
	vertices[4].Set(0.0f * PSI, -100.0f * PSI);
	vertices[5].Set(82.0f  *PSI, -66.0f * PSI);
	vertices[6].Set(100.0f * PSI, 0.0f * PSI);
	vertices[7].Set(67.0f * PSI, 67.0f * PSI);
	//Assign vertices to shape
	Shape.Set(vertices, vertexCount);
	//Assign shape to fixtureDef
	fixtureDef.shape = &Shape;
	//Assign fixtureDef to physics component
	phys->setFixtureDef(fixtureDef);

	// Sprite
	auto spr = asteroid->addComponent<SpriteComponent>();
	spr->setTextureRect(sf::IntRect(0, 0, 256, 256));
	spr->setTexure(ssAsteroids);

	//Add to collection
	asteroids.push_back(asteroid);
}

void GameScene::Update(const double& dt) {
	 
	//If less than 5 total asteroids, spawn another big asteroid.
	if (asteroids.size() < 5)
	{
		SpawnAsteroid();
	}

	Scene::Update(dt);
}

