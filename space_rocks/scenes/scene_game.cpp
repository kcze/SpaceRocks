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
#include <queue>

using namespace std;
using namespace sf;

std::vector < std::shared_ptr<Entity> > arrows; //Up, Right, Down, Left
std::shared_ptr<Entity> game;
std::shared_ptr<Entity> shop;
std::shared_ptr<PanelComponent> gamePanel;
std::shared_ptr<PanelComponent> shopPanel;
bool shopVisible;

std::vector<std::shared_ptr<Entity>> asteroids;
std::vector<std::shared_ptr<Entity>> enemies;
std::queue< std::pair<unsigned int, unsigned int> > enemyQueue;
unsigned int maxEnemyPop = 0;

std::shared_ptr<sf::Texture> ssAsteroids;
default_random_engine randomGenerator((int)time(NULL));
uniform_real_distribution<float> distrib(-1.0f, 1.0f);
float PSI = Physics::physicsScaleInv;

//TODO: Convert asteroid spawning to que system?
unsigned int maxAsteroidPop = 0;
unsigned int maxAsteroidsTotal = 5;
unsigned int asteroidsSoFar = 0;

unsigned int curRound = 0;
unsigned int curWave = 1;

bool enemiesQueued = false;
bool newRound = true;

std::shared_ptr<Entity> player;
std::shared_ptr<DestructibleComponent> playerDestructible;
std::string str;

static std::map < std::pair<unsigned int, unsigned int>, std::vector< std::tuple<unsigned int, unsigned int, unsigned int> > > _waveData =
{
	// ROUND 1 
	//Wave 1
	{make_pair < unsigned int, unsigned int>(1,1), //Key
		{
			make_tuple<unsigned int, unsigned int, unsigned int>(1 , 2, 1) //squadron 1
		}
	},
	//Wave 2
	{make_pair < unsigned int, unsigned int>(1,2), //Key
		{
			make_tuple<unsigned int, unsigned int, unsigned int>(2 , 2, 4) //squadron 1
		}
	},

	// ROUND 2
	//Wave 1
	{make_pair < unsigned int, unsigned int>(2,1), //Key
		{
			make_tuple<unsigned int, unsigned int, unsigned int>(1 , 2, 1), //squadron 1
			make_tuple<unsigned int, unsigned int, unsigned int>(1 , 2, 3)	//squadron 2
		}
	},
	//Wave 2
	{make_pair < unsigned int, unsigned int>(2,2), //Key
		{
			make_tuple<unsigned int, unsigned int, unsigned int>(1 , 2, 4), //squadron 1
			make_tuple<unsigned int, unsigned int, unsigned int>(1 , 2, 2)	//squadron 2
		}
	},
	//Wave 3
	{make_pair < unsigned int, unsigned int>(2,3), //Key
		{
			make_tuple<unsigned int, unsigned int, unsigned int>(1 , 3, 1) //squadron 1
		}
	},

	// ROUND 3
	//Wave 1
	{make_pair < unsigned int, unsigned int>(3,1), //Key
		{
			make_tuple<unsigned int, unsigned int, unsigned int>(2 , 2, 4), //squadron 1
			make_tuple<unsigned int, unsigned int, unsigned int>(1 , 3, 2)	//squadron 2
		}
	},
	//Wave 2
	{make_pair < unsigned int, unsigned int>(3,2), //Key
		{
			make_tuple<unsigned int, unsigned int, unsigned int>(2 , 3, 1), //squadron 1
			make_tuple<unsigned int, unsigned int, unsigned int>(1 , 2, 4)	//squadron 2
		}
	},
	//Wave 3
	{make_pair < unsigned int, unsigned int>(3,3), //Key
		{
			make_tuple<unsigned int, unsigned int, unsigned int>(3 , 2, 3) //squadron 1
		}
	}
};


MyContactListener contactListenerInstance;
DebugDraw debugDrawInstance;

void setShopVisible(bool visible)
{
	suppressPlayerControl = visible;
	shopVisible = visible;
	shopPanel->setVisible(visible);
}

void GameScene::load() {
	cout << "Game Scene Load \n";	

	// Shop panel
	shop = makeEntity();
	shop->setPosition(sf::Vector2f(256.0f, GAMEY / 2));
	shopPanel = shop->addComponent<PanelComponent>(sf::Vector2f(0.5f, 0.5f), 96.0f);
	shopPanel->addText("Shop", 48.0f);
	shopPanel->addButton("Continue", []() { 
		setShopVisible(false); 
		//Start next round
		gameScene.roundwaveStart();
	});
	shopPanel->addButton("Menu", []() { Engine::changeScene(&menuScene); });
	setShopVisible(true);

	//Edge Arrows
	{
		//up
		auto arrowUp = makeEntity();
		arrowUp->setPosition(sf::Vector2f(GAMEX / 2, 64.0f));
		auto arSprite = arrowUp->addComponent<SpriteComponent>();
		arSprite->setTextureRect(IntRect(128, 0, 128, 128));
		arSprite->setTexure(Resources::get<sf::Texture>("arrows.png"));
		arSprite->setColor(sf::Color(255, 0, 0, 255));
		arrowUp->setRotation(-90.0f);
		//right
		auto arrowRight = makeEntity();
		arrowRight->setPosition(sf::Vector2f(GAMEX - 64.0f, GAMEY / 2));
		arSprite = arrowRight->addComponent<SpriteComponent>();
		arSprite->setTextureRect(IntRect(128, 0, 128, 128));
		arSprite->setTexure(Resources::get<sf::Texture>("arrows.png"));
		arSprite->setColor(sf::Color(255, 0, 0, 255));
		//down
		auto arrowDown = makeEntity();
		arrowDown->setPosition(sf::Vector2f(GAMEX / 2, GAMEY - 64.0f));
		arSprite = arrowDown->addComponent<SpriteComponent>();
		arSprite->setTextureRect(IntRect(128, 0, 128, 128));
		arSprite->setTexure(Resources::get<sf::Texture>("arrows.png"));
		arSprite->setColor(sf::Color(255, 0, 0, 255));
		arrowDown->setRotation(90.0f);
		//left
		auto arrowLeft = makeEntity();
		arrowLeft->setPosition(sf::Vector2f(64.0f, GAMEY / 2));
		arSprite = arrowLeft->addComponent<SpriteComponent>();
		arSprite->setTextureRect(IntRect(128, 0, 128, 128));
		arSprite->setTexure(Resources::get<sf::Texture>("arrows.png"));
		arSprite->setColor(sf::Color(255, 0, 0, 255));
		arrowLeft->setRotation(180.0f);
		//Add to collection
		arrows.push_back(arrowUp);
		arrows.push_back(arrowRight);
		arrows.push_back(arrowDown);
		arrows.push_back(arrowLeft);
		for (unsigned int i = 0; i < arrows.size(); i++)
			arrows[i]->setVisible(false);
	}

	// Player ship
	player = ShipFactory::makePlayer();
	player->getComponents<PhysicsComponent>()[0]->teleport(Vector2f(GAMEX / 2, GAMEY / 2));
	//DEBUG SUPER BULLET
	//player->getComponents<ShipComponent>()[0]->setBullet(5.0f, 14);

	playerDestructible = player->getComponents<DestructibleComponent>()[0];

	// Game panel
	game = makeEntity();
	game->setPosition(sf::Vector2f(64.0f, 16.0f));
	gamePanel = game->addComponent<PanelComponent>(sf::Vector2f(0.0f, 0.0f), 64.0f, true);

	// HP
	gamePanel->addText([]() -> std::string { 
		return to_string((int)round(playerDestructible->getHp())) + "/" +
			to_string((int)round(playerDestructible->getMaxHp()));
	});

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
	//gameScene.roundwaveStart();

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
		pos = sf::Vector2f(dLength(rG), -500.0f);
		break;
	//right
	case 2:
		pos = sf::Vector2f(GAMEX + 500.0f, dSide(rG));
		break;
	//down
	case 3:
		pos = sf::Vector2f(dLength(rG), GAMEY + 500.0f);
		break;
	//left
	case 4:
		pos = sf::Vector2f(-500.0f, dSide(rG));
		break;
	};

	//Make Enemy
	std::cout << "Enemy spawned at: " << pos << std::endl;
	auto enemy = ShipFactory::makeEnemy(id);
	enemy->getComponents<PhysicsComponent>()[0]->teleport(pos);
	//Add to collection
	enemies.push_back(enemy);
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

void GameScene::onKeyPressed(Keyboard::Key key)
{
	if (!gameScene.isLoaded())
		return;

	//todo temporary
	if (key == Keyboard::Tab)
	{
		setShopVisible(true);
	}

	if (!shopVisible)
		return;

	if (key == Keyboard::Up)
	{
		shopPanel->pointerPrevious();
	}
	else if (key == Keyboard::Down)
	{
		shopPanel->pointerNext();
	}
	else if (key == Keyboard::Enter)
	{
		shopPanel->executeButton();
	}

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
	while (!enemyQueue.empty())
	{
		//Get next enemy from spawn queue
		auto enemyData = enemyQueue.front();
		enemyQueue.pop();
		spawnEnemy(enemyData.first, enemyData.second);
	}
	//When all enemies are dead, Spawn next wave
	if (enemiesQueued && enemies.empty())
	{
		curWave++;

		//Set EQ to false before wave spawn to syncronise threads
		enemiesQueued = false;

		//If still more waves to come
		if (_waveData.count(make_pair(curRound, curWave)))
		{
			gameScene.roundwaveStart();
		}
		//Else when all waves are complete, Round complete
		else 
		{
			newRound = true;
			//Go to shop
			setShopVisible(true);
		}
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
	if (newRound)
	{
		//Initialise round
		curRound++;
		curWave = 1;
		maxAsteroidPop = 0;
		asteroidsSoFar = 0;
		//TODO: Damage to death all asteroid and bullet fragments

		//Countdown
		audioManager.playSound("voice_3");
		sf::sleep(sf::milliseconds(1000));
		audioManager.playSound("voice_2");
		sf::sleep(sf::milliseconds(1000));
		audioManager.playSound("voice_1");
		sf::sleep(sf::milliseconds(1000));
		newRound = false;
	}
	else
		sf::sleep(sf::milliseconds(3000));

	//Initiate Round!
	//Enemies
	gameScene.spawnWave();

	//Asteroids
	maxAsteroidPop++;
	sf::sleep(sf::milliseconds(1000));
	maxAsteroidPop++;
	sf::sleep(sf::milliseconds(1000));
	maxAsteroidPop++;

} sf::Thread rst(&roundStartThread);

void GameScene::roundwaveStart()
{

	rst.launch();
	return;
}

void GameScene::spawnWave() {


	//Get data for current wave
	auto etData = _waveData[std::make_pair(curRound, curWave)];
	std::vector <unsigned int> sides;

	//For each squadron in wave
	for (unsigned int i = 0; i < etData.size(); i++)
	{
		//For each enemy in squadron
		for (unsigned int j = 0; j < std::get<0>(etData[i]); j++)
		{
			unsigned int id = std::get<1>(etData[i]);
			unsigned int side = std::get<2>(etData[i]);
			sides.push_back(side);
			enemyQueue.push(std::make_pair(id, side));
		}
	}

	//Sound
	audioManager.playSound("wave_approaching");
	//Arrow flashes. Eight flashes to match SFX
	for (unsigned int i = 0; i < 8; i++)
	{
		//On
		for(unsigned int j = 0; j < sides.size(); j++)
			arrows[sides[j]-1]->setVisible(true);
		sf::sleep(sf::milliseconds(125));
		//Off
		for (unsigned int j = 0; j < sides.size(); j++)
			arrows[sides[j] - 1]->setVisible(false);
		sf::sleep(sf::milliseconds(125));
	}


	enemiesQueued = true;
}