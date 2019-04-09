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

using namespace std;
using namespace sf;


std::vector<std::shared_ptr<Entity>> asteroids;
std::shared_ptr<sf::Texture> ssAsteroids;

void GameScene::Load() {
	cout << "Game Scene Load \n";
	{
		auto txt = makeEntity();
	}

	//// Load spritesheets
	//if (!ssAsteroids->loadFromFile("res/img/asteroid-1.png")) {
	//	std::cerr << "Failed to load asteroid spritesheet!" << std::endl;
	//}


	srand(time(NULL));
	setLoaded(true);
}

void GameScene::SpawnAsteroid()
{
	//asteroids.shrink_to_fit(); //TODO: Ensure list is shrunk when asteroid is destroyed...
	
	auto asteroid = makeEntity();
	// Generate random position off screen
	float rx = ((1.0f - 0.0f) * ((float)rand() / RAND_MAX)) + 0.0f;
	float ry = ((1.0f - 0.0f) * ((float)rand() / RAND_MAX)) + 0.0f;
	sf::Vector2f dir = sf::Vector2f(rx, ry);
	dir = sf::normalize<float>(dir);
	dir *= 800.0f;
	asteroid->setPosition(dir);
	
	// Physics
	//auto phys = asteroid->addComponent<PhysicsComponent>(true, sf::Vector2f(10.0f, 10.0f));
	//Set velocity back towards center
	//TODO: Random variation to prevent all asteroids heading straight to center.
	//phys->setVelocity(sf::Vector2f(-rx, -ry));

	//Sprite
	auto spr = asteroid->addComponent<SpriteComponent>();
	spr->setTextureRect(sf::IntRect(0, 0, 256, 256));
	spr->setTexure(ssAsteroids);

	//Add to collection
	asteroids.push_back(asteroid);
}

void GameScene::Update(const double& dt) {
	 

	if (sf::Keyboard::isKeyPressed(Keyboard::Space)) {
		cout << "Game Scene " << dt << "\n";
	}
	
	//If less than 5 total asteroids, spawn another big asteroid.
	//if (asteroids.size() < 5)
	//	SpawnAsteroid();

	Scene::Update(dt);
}

