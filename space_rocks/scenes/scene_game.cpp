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

std::shared_ptr<Entity> game;
std::shared_ptr<Entity> shop;

std::shared_ptr<PanelComponent> gamePanel;
std::shared_ptr<PanelComponent> shopPanel;

std::shared_ptr<Entity> gameOver1;
std::shared_ptr<Entity> gameOver2;
std::shared_ptr<PanelComponent> gameOverPanel;
std::shared_ptr<Entity> initial1;
std::shared_ptr<Entity> initial2;
std::shared_ptr<Entity> initial3;
std::shared_ptr<Entity> carat;

std::vector < std::shared_ptr<Entity> > arrows; //Up, Right, Down, Left
std::vector<std::shared_ptr<Entity>> asteroids;
std::vector<std::shared_ptr<Entity>> enemies;
std::queue< std::pair<unsigned int, unsigned int> > enemyQueue;

default_random_engine randomGenerator((int)time(NULL));
uniform_real_distribution<float> distrib(-1.0f, 1.0f);

float PSI = Physics::physicsScaleInv;

unsigned int maxAsteroidPop;
unsigned int curRound;
unsigned int curWave;
unsigned int maxEnemyPop;

bool enemiesQueued;
bool newRound;
bool toMenu;
bool shopVisible;
bool enteringText;

std::shared_ptr<DestructibleComponent> playerDestructible;
std::string str;
std::stringstream playerName;

MyContactListener contactListenerInstance;
DebugDraw debugDrawInstance;


static std::map < std::pair<unsigned int, unsigned int>, std::vector< std::tuple<unsigned int, unsigned int, unsigned int> > > _waveData =
{
	// ROUND 1 
	//Wave 1
	{make_pair < unsigned int, unsigned int>(1,1), //Key
		{
			make_tuple<unsigned int, unsigned int, unsigned int>(1 , 2, 1)	//squadron 1
		}
	},
	//Wave 2
	{make_pair < unsigned int, unsigned int>(1,2), //Key
		{
			make_tuple<unsigned int, unsigned int, unsigned int>(2 , 2, 4)	//squadron 1
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
			make_tuple<unsigned int, unsigned int, unsigned int>(1 , 3, 1)	//squadron 1
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
			make_tuple<unsigned int, unsigned int, unsigned int>(3 , 2, 3)	//squadron 1
		}
	},

	// ROUND 4
	//Wave 1
	{make_pair < unsigned int, unsigned int>(4,1), //Key
		{
			make_tuple<unsigned int, unsigned int, unsigned int>(2 , 2, 1), //squadron 1
			make_tuple<unsigned int, unsigned int, unsigned int>(2 , 3, 3)	//squadron 2
		}
	},
	//Wave 2
	{make_pair < unsigned int, unsigned int>(4,2), //Key
		{
			make_tuple<unsigned int, unsigned int, unsigned int>(2 , 2, 4), //squadron 1
			make_tuple<unsigned int, unsigned int, unsigned int>(2 , 3, 2)	//squadron 2
		}
	},
	//Wave 3
	{make_pair < unsigned int, unsigned int>(4,3), //Key
		{
			make_tuple<unsigned int, unsigned int, unsigned int>(1, 2, 1),	//squadron 1
			make_tuple<unsigned int, unsigned int, unsigned int>(1, 2, 2),	//squadron 1
			make_tuple<unsigned int, unsigned int, unsigned int>(1, 2, 3),	//squadron 1
			make_tuple<unsigned int, unsigned int, unsigned int>(1, 2, 4)	//squadron 1
		}
	}, 

	// ROUND 5
	//Wave 1
	{make_pair < unsigned int, unsigned int>(5,1), //Key
		{
			make_tuple<unsigned int, unsigned int, unsigned int>(1, 2, 4),	//squadron 1
			make_tuple<unsigned int, unsigned int, unsigned int>(1, 3, 2),	//squadron 2
			make_tuple<unsigned int, unsigned int, unsigned int>(1, 4, 1)	//squadron 3
		}
	},
	//Wave 2
	{make_pair < unsigned int, unsigned int>(5,2), //Key
		{
			make_tuple<unsigned int, unsigned int, unsigned int>(1, 4, 4),	//squadron 1
			make_tuple<unsigned int, unsigned int, unsigned int>(1, 4, 2),	//squadron 2
			make_tuple<unsigned int, unsigned int, unsigned int>(1, 3, 3)	//squadron 2
		}
	},
	//Wave 3
	{make_pair < unsigned int, unsigned int>(5,3), //Key
		{
			make_tuple<unsigned int, unsigned int, unsigned int>(1, 2, 1),	//squadron 1
			make_tuple<unsigned int, unsigned int, unsigned int>(1, 2, 3),	//squadron 1
			make_tuple<unsigned int, unsigned int, unsigned int>(1, 4, 4),	//squadron 1
			make_tuple<unsigned int, unsigned int, unsigned int>(1, 4, 2)	//squadron 1
		}
	},
	//Wave 4
	{ make_pair < unsigned int, unsigned int>(5,4), //Key
		{
			make_tuple<unsigned int, unsigned int, unsigned int>(1, 5, 1)	//squadron 1
		}
	}
};



void setShopVisible(bool visible)
{
	suppressPlayerControl = visible;
	shopVisible = visible;//todo maybe not needed?
	shopPanel->setVisible(visible);
}

void setGameoverVisible(bool visible)
{
	if (!visible)
	{
		gameOver1->setVisible(false);
		gameOver2->setVisible(false);
		gameOverPanel->setVisible(false);
		initial1->setVisible(false);
		initial2->setVisible(false);
		initial3->setVisible(false);
		carat->setVisible(false);
	}
	else
	{
		suppressPlayerControl = true;
		setShopVisible(false);
	}
}

void GameScene::load() {
	cout << "Game Scene Load \n";
	//Reset
	{

		std::queue<std::pair<unsigned int, unsigned int>>().swap(enemyQueue);
		destroyAll();
		maxAsteroidPop = 0;
		curRound = 0;
		curWave = 1;
		maxEnemyPop = 0;
		enteringText = false;
		enemiesQueued = false;
		newRound = true;
		toMenu = false;
		playerName.str("");
		playerName.clear();
	}

	// Player ship
	player1.swap(ShipFactory::makePlayer());
	player1->getComponents<PhysicsComponent>()[0]->teleport(Vector2f(GAMEX / 2, GAMEY / 2));
	playerDestructible = player1->getComponents<DestructibleComponent>()[0];


	// Shop panel
	{
		shop = makeEntity();
		shop->setPosition(sf::Vector2f(256.0f, GAMEY / 2 + 64.0f));
		shopPanel = shop->addComponent<PanelComponent>(sf::Vector2f(0.5f, 0.5f), 96.0f);
		shopPanel->addText("Shop", 78.0f);
		//ITEMS
		// Repair 1HP
		shopPanel->addButton("Repair 1HP [$2]", []() {
			//if player has enough credits, purchase
			if (player1->getComponents<PlayerComponent>()[0]->tryPurchase(2))
			{
				//Repair
				player1->getComponents<DestructibleComponent>()[0]->repair(1);
			}
		});
		// Repair All
		shopPanel->addButton("Repair ALL [$8]", []() {
			//if player has enough credits, purchase
			if (player1->getComponents<PlayerComponent>()[0]->tryPurchase(8))
			{
				//Repair
				player1->getComponents<DestructibleComponent>()[0]->repair(player1->getComponents<DestructibleComponent>()[0]->getMaxHp());
			}
		});
		// Damage Upgrade
		shopPanel->addButton(
			[]() -> std::string { return "Damage Up [$" + std::to_string(player1->getComponents<ShipComponent>()[0]->getBullet()._id + 4) + "]"; },
			[]() 
		{
			//if player has enough credits, purchase
			player1->getComponents<PlayerComponent>()[0]->tryUpgradeDamage();
		});
		// Rate of Fire Upgrade
		shopPanel->addButton(
			[]() -> std::string { return "Firerate Up [$" + std::to_string((int)(80 - 100 * player1->getComponents<ShipComponent>()[0]->getReload())) + "]"; },
			[]()
		{
			//if player has enough credits, purchase
			player1->getComponents<PlayerComponent>()[0]->tryUpgradeROF();
		});
		// Ready
		shopPanel->addButton("Ready", []() {
			setShopVisible(false);
			//Start next round
			gameScene.roundwaveStart();
		});

		//TODO: Fix navigation back to menu and add Save button
		//shopPanel->addButton("Menu", []() { Engine::changeScene(&menuScene); });

		setShopVisible(true);
	}

	// Gameover screen
	{
		gameOver1 = makeEntity();
		gameOver1->setPosition(sf::Vector2f(GAMEX / 2 - 200.0f, GAMEY / 2 - 100.0f));
		auto t = gameOver1->addComponent<TextComponent>();
		t->setText("Game");
		t->setSize(200.0f);

		gameOver2 = makeEntity();
		gameOver2->setPosition(sf::Vector2f(GAMEX / 2 + 200.0f, GAMEY / 2 - 100.0f));
		t = gameOver2->addComponent<TextComponent>();
		t->setText("Over");
		t->setSize(200.0f);

		initial1 = makeEntity();
		initial1->setPosition(sf::Vector2f(GAMEX / 2 - 64.0f, GAMEY / 2 + 64.0f));
		t = initial1->addComponent<TextComponent>();
		t->setText("A");
		t->setSize(100.0f);		
		
		carat = makeEntity();
		carat->setPosition(sf::Vector2f(GAMEX / 2 - 64.0f, GAMEY / 2 + 112.0f));
		t = carat->addComponent<TextComponent>();
		t->setText("^");
		t->setSize(100.0f);		
		
		initial2 = makeEntity();
		initial2->setPosition(sf::Vector2f(GAMEX / 2, GAMEY / 2 + 64.0f));
		t = initial2->addComponent<TextComponent>();
		t->setText("A");
		t->setSize(100.0f);

		initial3 = makeEntity();
		initial3->setPosition(sf::Vector2f(GAMEX / 2 + 64.0f, GAMEY / 2 + 64.0f));
		t = initial3->addComponent<TextComponent>();
		t->setText("A");
		t->setSize(100.0f);

		auto go = makeEntity();
		go->setPosition(sf::Vector2f(GAMEX / 2, GAMEY / 2 + 256.0f));
		gameOverPanel = go->addComponent<PanelComponent>(sf::Vector2f(0.5f, 0.5f), 96.0f);
		gameOverPanel->addButton("Menu", []() { toMenu = true; });

		setGameoverVisible(false);
	}

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

	// Game panel (UI)
	{
		game = makeEntity();
		game->setPosition(sf::Vector2f(420.0f, 16.0f));
		gamePanel = game->addComponent<PanelComponent>(sf::Vector2f(0.0f, 0.0f), 192.0f, true);
		
		// HP
		gamePanel->addText([]() -> std::string {
			stringstream ss;
			ss << fixed << setprecision(1) << playerDestructible->getHp() << "/" << playerDestructible->getMaxHp();
			return ss.str();
		});

		//Credits
		gamePanel->addText([]() -> std::string {
			return "Credits: " + std::to_string(player1->getComponents<PlayerComponent>()[0]->getCoins());
		});

		//Score (Leave last as gets long!)
		gamePanel->addText([]() -> std::string {
			return "Score: " + std::to_string(player1->getComponents<PlayerComponent>()[0]->getScore());
		});

		//Highest Score
		gamePanel->addText([]() -> std::string {
			if(highscores.empty())
				return "Highscore: 0";
			else
				return "Highscore: " + std::to_string((--highscores.end())->first);
		});
	}


	//Creat edges
	createEdges();

	//Set contact listener
	auto body = player1->getComponents<PhysicsComponent>()[0]->getBody();
	auto world = body->GetWorld();
	world->SetContactListener(&contactListenerInstance);

	//Set Debug Draw
	world->SetDebugDraw(&debugDrawInstance);
	debugDrawInstance.SetFlags(b2Draw::e_shapeBit);

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
	auto asteroid = AsteroidFactory::makeAsteroid(11, center + dir * 770.0f);

	//Set velocity back towards center
	//TODO: Random variation to prevent all asteroids heading straight to center.
	asteroid->getComponents<PhysicsComponent>()[0]->setVelocity(sf::Vector2f(dir.x, -dir.y) * -50.0f);

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

void GameScene::onKeyPressed(std::variant<Keyboard::Key, unsigned int> k)
{
	if (!gameScene.isLoaded())
		return;

	Input::KeyCode key = Input::getKeyCode(k);

	// Handling game over controls
	if (key == Input::P1_FIRE && gameOverPanel->isVisible())
	{
		gameOverPanel->executeButton();
	}

	// Handling shop controls
	if (!shopVisible)
		return;

	if (key == Input::P1_THRUST)
	{
		shopPanel->pointerPrevious();
	}
	else if (key == Input::P1_DOWN)
	{
		shopPanel->pointerNext();
	}
	else if (key == Input::P1_FIRE)
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

	if (player1->isAlive())
	{
		//Spawn Asteroids
		if (asteroids.size() < maxAsteroidPop)
	{
		spawnAsteroid();
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
				//If there is no next round
				if (!_waveData.count(make_pair(curRound + 1, 1)))
				{
					//Game over, player wins!
					gameOver1->getComponents<TextComponent>()[0]->setText("You");
					gameOver2->getComponents<TextComponent>()[0]->setText("Win!");
					player1->getComponents<DestructibleComponent>()[0]->damage(player1->getComponents<DestructibleComponent>()[0]->getMaxHp());
				}
				
				//Damage to death all asteroid and bullet fragments
				gameScene.destroyAll();
				newRound = true;
				maxAsteroidPop = 0;
				//Go to shop
				setShopVisible(true);
			}
		}
	}


	//TODO: Less hacky way of getting world, similar is also used in load
	//auto world = asteroids[0]->getComponents<PhysicsComponent>()[0]->getBody()->GetWorld();
	//world->DrawDebugData();

	if (toMenu)
		gotoMenu();

	Scene::update(dt);
}

void GameScene::onTextEntered(std::string text)
{
	if (!enteringText)
		return;
	
	cout << "Enter Initals" << endl;

	//If all 3 entered then return
	if (playerName.str().size() >= 3)
	{
		enteringText = false;
		return;
	}

	//Only accept letters
	if (!isalpha(text[0]))
		return;

	// Add character to name
	playerName << text;
	// Display character
	switch (playerName.str().size())
	{
	case 1:
		initial1->getComponents<TextComponent>()[0]->setText(text);
		break;
	case 2:
		initial2->getComponents<TextComponent>()[0]->setText(text);
		break;
	case 3: 
		initial3->getComponents<TextComponent>()[0]->setText(text);
		carat->setVisible(false);

		//Add score to highscores.
		const std::string& s = playerName.str();
		highscores.emplace(player1->getComponents<PlayerComponent>()[0]->getScore(), s);

		if (highscores.size() > 10)
			highscores.erase(highscores.begin());

		return;
	}

	//Move Carat along
	carat->setPosition(sf::Vector2f(carat->getPosition().x + 64.0f, carat->getPosition().y));
}

void pDThread()
{
	sf::sleep(sf::milliseconds(2000));
	audioManager.playSound("game_over");
	setGameoverVisible(true);

	gameOver1->setVisible(true);
	sf::sleep(sf::milliseconds(750));
	gameOver2->setVisible(true);

	maxAsteroidPop = 0;
	gameScene.destroyAll();
	sf::sleep(sf::milliseconds(100));
	setShopVisible(false);
	sf::sleep(sf::milliseconds(650));
	gameOverPanel->setVisible(true);
	sf::sleep(sf::milliseconds(150));
	initial1->setVisible(true);
	sf::sleep(sf::milliseconds(150));
	initial2->setVisible(true);
	sf::sleep(sf::milliseconds(150));
	initial3->setVisible(true);
	sf::sleep(sf::milliseconds(150));
	carat->setVisible(true);
	enteringText = true;

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
		//Countdown
		audioManager.playSound("voice_3");
		sf::sleep(sf::milliseconds(1000));
		audioManager.playSound("voice_2");
		sf::sleep(sf::milliseconds(1000));
		audioManager.playSound("voice_1");
		sf::sleep(sf::milliseconds(1000));
		newRound = false;
		maxAsteroidPop = 3;
	}
	else
		sf::sleep(sf::milliseconds(3000));

	//Initiate Round!
	//Enemies
	gameScene.spawnWave();


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

	for (unsigned int i = 0; i < 8; i++)
	{
		//Arrow flashes. Eight flashes to match SFX
		if (arrows.size() == 0)
			return;
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


//Damage to death all non-player destructibles in the scene
void GameScene::destroyAll()
{
	for (unsigned int i = 0; i < gameScene.ents.list.size(); i++)
	{
		std::shared_ptr<Entity> current = gameScene.ents.list[i];

		//If Destructible and not player or particle, kill
		if (!current->getComponents<DestructibleComponent>().empty() && current->getComponents<PlayerComponent>().empty() && current->getComponents<DestructibleComponent>()[0]->getHp() != FLT_MIN)
		{
			//If Asteroid, delete (as destroying too many objects causes lag, and asteroids spawn more fragments)
			if (current->getComponents<PhysicsComponent>()[0]->getFixture()->GetFilterData().categoryBits == ASTEROIDS)
				current->setForDelete();

			//Else kill
			else
				current->getComponents<DestructibleComponent>()[0]->damage(FLT_MAX);
		}

		current.reset();
	}
}

// Switch scene to menu safely
void GameScene::gotoMenu()
{
	//Stop all threads
	pdthread.terminate();
	rst.terminate();

	// Resetting all shared_ptr
	player1->getComponents<PhysicsComponent>()[0]->~PhysicsComponent();
	playerDestructible.reset();
	player1->setForDelete();
	player1.reset();

	gamePanel.reset();
	game->setForDelete();

	shopPanel.reset();
	shop->setForDelete();

	gameOverPanel.reset();
	gameOver1->setForDelete();
	gameOver2->setForDelete();

	for (auto p : asteroids)
		p->setForDelete();

	asteroids.clear();

	for (auto p : enemies)
		p->setForDelete();

	enemies.clear();

	for (auto p : arrows)
		p->setForDelete();

	arrows.clear();

	toMenu = false;

	Engine::changeScene(&menuScene);
}
