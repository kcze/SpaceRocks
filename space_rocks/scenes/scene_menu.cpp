#include "scene_menu.h"
#include "../components/components.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <vector>
#include "../input.h"
#include "system_renderer.h"
#include <functional>

using namespace std;
using namespace sf;

//Entities
std::shared_ptr<Entity> txtTitle;
/*std::shared_ptr<Entity> txtNewGame;
std::shared_ptr<Entity> txtLoad;
std::shared_ptr<Entity> txtHighScores;
std::shared_ptr<Entity> txtOptions;
std::shared_ptr<Entity> txtExit;
std::shared_ptr<Entity> menuCursor;*/

std::shared_ptr<Entity> menu;
std::shared_ptr<PanelComponent> menuPanel;

unsigned int cursorOffset = 100.0f;
unsigned int target = 1;
unsigned int numOptions = 5;
bool newUpPress = true;
bool newDownPress = true;

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
	Engine::getWindow().setSize(screensize);
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
	Engine::getWindow().setView(v);
}

void MenuScene::load() {
	cout << "Menu Load \n";
	
	// Title
	txtTitle = makeEntity();
	auto txt = txtTitle->addComponent<TextComponent>("SPACE ROCKS");
	txt->setSize(64);
	txtTitle->setPosition(Vector2f(640.0f, 64.0f));
	
	// Menu
	menu = makeEntity();
	menu->setPosition(sf::Vector2f(GAMEX / 2, GAMEY / 2 + 96.0f));
	menuPanel = menu->addComponent<PanelComponent>(sf::Vector2f(0.5f, 0.5f), 96.0f);
	menuPanel->addButton("Start", []() { Engine::changeScene(&gameScene); });
	menuPanel->addButton("Load", []() {});
	menuPanel->addButton("High Scores", []() {});
	menuPanel->addButton("Settings", []() {});
	menuPanel->addButton("Exit", []() {});

	UpdateScaling();
	setLoaded(true);
}

void MenuScene::onKeyPressed(Keyboard::Key key)
{
	if (!gameScene.isLoaded())
	{
		if (key == Keyboard::Up)
		{
			audioManager.playSound("menu_cycle");
			menuPanel->pointerPrevious();
		}
		else if (key == Keyboard::Down)
		{
			audioManager.playSound("menu_cycle");
			menuPanel->pointerNext();
		}
		else if (key == Keyboard::Enter)
		{
			audioManager.playSound("menu_select");
			menuPanel->executeButton();
		}
	}
}

void MenuScene::update(const double& dt) {
  
  Scene::update(dt);
}
