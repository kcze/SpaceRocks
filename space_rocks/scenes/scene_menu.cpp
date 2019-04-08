#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <vector>
#include "../input.h"
#include "system_renderer.h"

using namespace std;
using namespace sf;

//Entities
std::shared_ptr<Entity> txtTitle;
std::shared_ptr<Entity> txtNewGame;
std::shared_ptr<Entity> txtLoad;
std::shared_ptr<Entity> txtHighScores;
std::shared_ptr<Entity> txtOptions;
std::shared_ptr<Entity> txtExit;
std::shared_ptr<Entity> menuCursor;

unsigned int cursorOffset = 100.0f;

// Create FloatRect to fits Game into Screen while preserving aspect
sf::FloatRect CalculateViewport(const sf::Vector2u& screensize,
	const sf::Vector2u& gamesize) {

	const Vector2f screensf(screensize.x, screensize.y);
	const Vector2f gamesf(gamesize.x, gamesize.y);
	const float gameAspect = gamesf.x / gamesf.y;
	const float screenAspect = screensf.x / screensf.y;
	float scaledWidth;  // final size.x of game viewport in piels
	float scaledHeight; //final size.y of game viewport in piels
	bool scaleSide = false; // false = scale to screen.x, true = screen.y

	//Work out which way to scale
	if (gamesize.x > gamesize.y) { // game is wider than tall
	  // Can we use full width?
		if (screensf.y < (screensf.x / gameAspect)) {
			//no, not high enough to fit game height
			scaleSide = true;
		}
		else {
			//Yes, use all width available
			scaleSide = false;
		}
	}
	else { // Game is Square or Taller than Wide
   // Can we use full height?
		if (screensf.x < (screensf.y * gameAspect)) {
			// No, screensize not wide enough to fit game width
			scaleSide = false;
		}
		else {
			// Yes, use all height available
			scaleSide = true;
		}
	}

	if (scaleSide) { // use max screen height
		scaledHeight = screensf.y;
		scaledWidth = floor(scaledHeight * gameAspect);
	}
	else { //use max screen width
		scaledWidth = screensf.x;
		scaledHeight = floor(scaledWidth / gameAspect);
	}

	//calculate as percent of screen
	const float widthPercent = (scaledWidth / screensf.x);
	const float heightPercent = (scaledHeight / screensf.y);

	return sf::FloatRect(0, 0, widthPercent, heightPercent);
}

void UpdateScaling()
{
	const sf::Vector2u screensize(1280, 720);
	const sf::Vector2u gamesize(GAMEX, GAMEY);
	//set View as normal
	Engine::GetWindow().setSize(screensize);
	sf::FloatRect visibleArea(0.f, 0.f, gamesize.x, gamesize.y);
	auto v = sf::View(visibleArea);
	// figure out how to scale and maintain aspect;
	auto viewport = CalculateViewport(screensize, gamesize);
	//Optionally Center it
	bool centered = true;
	if (centered) {
		viewport.left = (1.0 - viewport.width) * 0.5;
		viewport.top = (1.0 - viewport.height) * 0.5;
	}
	//set!
	v.setViewport(viewport);
	Engine::GetWindow().setView(v);
}

void MenuScene::Load() {
	cout << "Menu Load \n";
	{
		// Title
		txtTitle = makeEntity();
		auto txt = txtTitle->addComponent<TextComponent>("SPACE ROCKS");
		txt->SetSize(64);
		txtTitle->setPosition(Vector2f(640.0f, 32.0f));

		// Menu Options
		//New Game
		txtNewGame = makeEntity();
		txt = txtNewGame->addComponent<TextComponent>("New Game");
		txt->SetSize(32);
		txtNewGame->setPosition(Vector2f(640.0f, 192.0f));
		//Load
		txtLoad = makeEntity();
		txt = txtLoad->addComponent<TextComponent>("Load");
		txtLoad->setPosition(Vector2f(640.0f, 240.0f));
		txt->SetSize(32);
		//HighScores
		txtHighScores = makeEntity();
		txt = txtHighScores->addComponent<TextComponent>("HighScores");
		txtHighScores->setPosition(Vector2f(640.0f, 288.0f));
		txt->SetSize(32);
		//Options
		txtOptions = makeEntity();
		txt = txtOptions->addComponent<TextComponent>("Options");
		txtOptions->setPosition(Vector2f(640.0f, 336.0f));
		txt->SetSize(32);
		//Exit
		txtExit = makeEntity(); 
		txt = txtExit->addComponent<TextComponent>("Exit");
		txtExit->setPosition(Vector2f(640.0f, 384.0f));
		txt->SetSize(32);

		// Cursor
		menuCursor = makeEntity();
		auto img = menuCursor->addComponent<ShapeComponent>();
		img->setShape<sf::CircleShape>(10.0f);
		img->SetAnchor(sf::Vector2f(0.5f, 0.3f));

		menuCursor->setPosition(sf::Vector2f(
			txtNewGame->getPosition().x - cursorOffset,
			txtNewGame->getPosition().y
		));

	}
	UpdateScaling();
	setLoaded(true);
}

void MenuScene::Update(const double& dt) {
  // cout << "Menu Update "<<dt<<"\n";

  if (sf::Keyboard::isKeyPressed(Keyboard::Enter)) {
	  cout << "Changing level...\n";
    Engine::ChangeScene(&gameScene);
  }

  if (Input::isKeyDown(Input::KeyCode::P1_FIRE)) {
	  cout << "Player 1 Fire works!\n";

  }
  
  Scene::Update(dt);
}

