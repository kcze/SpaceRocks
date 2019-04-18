#include "scene_game.h"
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
#include "..\asteroid_factory.h"
#include "..\components\components.h"
#include <ctime>
#include "..\contact_listener.h"
#include "..\debug_draw.h"


using namespace std;
using namespace sf;

std::shared_ptr<Entity> game;
std::shared_ptr<PanelComponent> gamePanel;

std::vector<std::shared_ptr<Entity>> asteroids;
std::vector<std::shared_ptr<Entity>> enemies;

std::shared_ptr<sf::Texture> ssAsteroids;
default_random_engine randomGenerator((int)time(NULL));
uniform_real_distribution<float> distrib(-1.0f, 1.0f);
float PSI = Physics::physicsScaleInv;
unsigned int maxAsteroidPop = 0;
unsigned int maxAsteroidsTotal = 5;
unsigned int asteroidsSoFar = 0;

MyContactListener contactListenerInstance;
DebugDraw debugDrawInstance;


void GameScene::load() {
	cout << "Game Scene Load \n";
	{
		// Game panel
		game = makeEntity();
		game->setPosition(sf::Vector2f(16.0f, 16.0f));
		gamePanel = game->addComponent<PanelComponent>(sf::Vector2f(0.0f, 0.0f));
		gamePanel->addText([]() -> std::string { time_t now = time(0); return std::ctime(&now); });
	}

	// Player ship
	auto player = ShipFactory::makePlayer();
	player->getComponents<PhysicsComponent>()[0]->teleport(Vector2f(GAMEX / 2, GAMEY / 2));
	//DEBUG SUPER BULLET
	//player->getComponents<ShipComponent>()[0]->setBullet(5.0f, 14);



	//Creat edges
	createEdges();

	//Set contact listener
	auto body = player->getComponents<PhysicsComponent>()[0]->getBody();
	auto world = body->GetWorld();
	world->SetContactListener(&contactListenerInstance);

	//Set Debug Draw
	world->SetDebugDraw(&debugDrawInstance);
	debugDrawInstance.SetFlags(b2Draw::e_shapeBit);

	//Start Round 1
	gameScene.roundStart();

	setLoaded(true);
}

void GameScene::spawnAsteroid()
{	
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
	auto asteroid = AsteroidFactory::makeAsteroid(11, center + dir * 800.0f);

	//Set velocity back towards center
	//TODO: Random variation to prevent all asteroids heading straight to center.
	asteroid->getComponents<PhysicsComponent>()[0]->setVelocity(sf::Vector2f(dir.x, -dir.y) * -75.0f);

	//Add to collection
	asteroids.push_back(asteroid);
}

//Make enemy with given ID and spawn in scene from given direction
//Valid IDs: 2-5
//Directions: 1 = top, 2 = right, 3 = bottom, 4 = left
void GameScene::spawnEnemy(unsigned int id, unsigned int dir)
{	
	//Random5
	std::default_random_engine rG((int)time(NULL));
	std::uniform_real_distribution<float> dSide(200.0f, GAMEY - 200.0f);
	std::uniform_real_distribution<float> dLength(300.0f, GAMEX - 300.0f);

	//Choose spawn position
	sf::Vector2f pos;
	switch(dir)
	{ 
	//top
	case 1:
		pos = sf::Vector2f(dLength(rG), -50.0f);
		break;
	//right
	case 2:
		pos = sf::Vector2f(GAMEX + 50.0f, dSide(rG));
		break;
	//down
	case 3:
		pos = sf::Vector2f(dLength(rG), GAMEY + 50.0f);
		break;
	//left
	case 4:
		pos = sf::Vector2f(-50.0f, dSide(rG));
		break;
	};

	//Make Enemy
	auto test1 = ShipFactory::makeEnemy(id);
	test1->getComponents<PhysicsComponent>()[0]->teleport(pos);
	//Add to collection
	enemies.push_back(test1);
}

void GameScene::createEdges()
{
	// Create entity
	auto edges = makeEntity();
	edges->setPosition(sf::Vector2f(0.0f, 0.0f));

	// Physics
	auto phys = edges->addComponent<PhysicsComponent>(false, sf::Vector2f(1.0f, 1.0f));
	//Get corners
	b2Vec2 upLeft = b2Vec2(0.0f, 0.0f);
	b2Vec2 downLeft = b2Vec2(0.0f, -GAMEY * PSI);
	b2Vec2 downRight = b2Vec2(GAMEX * PSI, -GAMEY * PSI);
	b2Vec2 upRight = b2Vec2(GAMEX * PSI, 0.0f);
	//Create Shape
	b2EdgeShape edgeShape;
	//Create Fixtures
	b2FixtureDef fixtureDef;
	fixtureDef.filter.categoryBits = EDGE;
	fixtureDef.filter.maskBits = PLAYER_SHIP;
	// left
	edgeShape.Set(upLeft, downLeft);
	fixtureDef.shape = &edgeShape;
	phys->setFixtureDef(fixtureDef);
	// bottom
	edgeShape.Set(downLeft, downRight);
	fixtureDef.shape = &edgeShape;
	phys->setFixtureDef(fixtureDef);
	// right
	edgeShape.Set(downRight, upRight);
	fixtureDef.shape = &edgeShape;
	phys->setFixtureDef(fixtureDef);
	// top
	edgeShape.Set(upRight, upLeft);
	fixtureDef.shape = &edgeShape;
	phys->setFixtureDef(fixtureDef);

}

void GameScene::update(const double& dt) {
	 
	//Check for deleted asteroids
	for (unsigned int i = 0; i < asteroids.size(); i++)
	{
		if (!asteroids[i]->isAlive())
		{
			asteroids.erase(asteroids.begin() + i);
			asteroids.shrink_to_fit();
		}
	}
	//Check for deleted enemies
	for (unsigned int i = 0; i < enemies.size(); i++)
	{
		if (!enemies[i]->isAlive())
		{
			enemies.erase(enemies.begin() + i);
			enemies.shrink_to_fit();
		}
	}

	//Spawn Asteroids
	if (asteroids.size() < maxAsteroidPop && asteroidsSoFar < maxAsteroidsTotal)
	{
		spawnAsteroid();
		asteroidsSoFar++;
	}

	//Spawn Enemies
	if (enemies.size() < 2)
	{
		spawnEnemy(2, 1);
	}


	//Round Complete
	if (asteroidsSoFar == maxAsteroidsTotal && asteroids.size() == 0)
	{
		//Reset
		maxAsteroidPop = 0;
		asteroidsSoFar = 0;
		//Start next round
		gameScene.roundStart();
	}

	//TODO: Less hacky way of getting world, similar is also used in load
	//auto world = asteroids[0]->getComponents<PhysicsComponent>()[0]->getBody()->GetWorld();
	//world->DrawDebugData();
	Scene::update(dt);
}

void pDThread()
{
	sf::sleep(sf::milliseconds(2000));
	audioManager.playSound("game_over");
} sf::Thread pdthread(&pDThread);


void GameScene::playerDeath()
{
	pdthread.launch();
	return;
}

void roundStartThread()
{
	//Countdown
	audioManager.playSound("voice_3");
	sf::sleep(sf::milliseconds(1000));
	audioManager.playSound("voice_2");
	sf::sleep(sf::milliseconds(1000));
	audioManager.playSound("voice_1");
	sf::sleep(sf::milliseconds(1000));
	audioManager.playSound("wave_approaching");
	//TODO: Show and Flash Enemy approaching indicator

	//Initiate Round!
	//Enemies

	//Asteroids
	maxAsteroidPop++;
	sf::sleep(sf::milliseconds(1000));
	maxAsteroidPop++;
	sf::sleep(sf::milliseconds(1000));
	maxAsteroidPop++;

} sf::Thread rst(&roundStartThread);


void GameScene::roundStart()
{
	rst.launch();
	return;
}