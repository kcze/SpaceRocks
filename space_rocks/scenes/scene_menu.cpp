#include "scene_menu.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <vector>
#include "system_renderer.h"
#include "..\components\components.h"
#include <functional>

using namespace std;
using namespace sf;

//Entities
std::shared_ptr<Entity> txtTitle;
std::shared_ptr<Entity> menu;
std::shared_ptr<Entity> settings;
std::shared_ptr<Entity> controls;
std::shared_ptr<Entity> high;
std::shared_ptr<Entity> graphics;
std::shared_ptr<PanelComponent> menuPanel;
std::shared_ptr<PanelComponent> settingsPanel;
std::shared_ptr<PanelComponent> controlsPanel;
std::shared_ptr<PanelComponent> highscoresPanel;
std::shared_ptr<PanelComponent> graphicsPanel;
PanelComponent* currentPanel;

Input::KeyCode changeKeyCode = (Input::KeyCode)-1;
Input::KeyCode changeTextEntered = (Input::KeyCode)-1;

bool switchWindow = false;

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
	const sf::Vector2u screensize = Engine::getWindowSize();	
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


void switchPanel(PanelComponent* panel)
{
	if (currentPanel != NULL)
		currentPanel->setVisible(false);

	currentPanel = panel;
	currentPanel->setVisible(true);
}

void MenuScene::load() {
	cout << "Menu Load \n";

	// Loading data from files
	Files::loadControls();
	highscores = Files::loadHighscores();

	
	// Title
	txtTitle.swap(makeEntity());
	auto txt = txtTitle->addComponent<TextComponent>("SPACE ROCKS");
	txt->setSize(64);
	txtTitle->setPosition(Vector2f(640.0f, 64.0f));
	
	// Menu
	menu = makeEntity();
	menu->setPosition(sf::Vector2f(GAMEX / 2, GAMEY / 2 + 96.0f));
	menuPanel = (menu->addComponent<PanelComponent>(sf::Vector2f(0.5f, 0.5f), 96.0f));
	menuPanel->addButton("Start", []() { gotoGame(); });
	menuPanel->addButton("High Scores", []() { switchPanel(highscoresPanel.get()); });
	menuPanel->addButton("Settings", []() { switchPanel(settingsPanel.get()); });
	menuPanel->addButton("Exit", []() { Engine::getWindow().close(); });
	menuPanel->setVisible(true);
	switchPanel(menuPanel.get());
	
	// Settings
	settings.swap(makeEntity());
	settings->setPosition(sf::Vector2f(GAMEX / 2, GAMEY / 2 + 96.0f));
	settingsPanel.swap(settings->addComponent<PanelComponent>(sf::Vector2f(0.5f, 0.5f), 96.0f));
	settingsPanel->addText("Settings", 48.0f);
	settingsPanel->addButton("Controls", []() { switchPanel(controlsPanel.get()); });
	settingsPanel->addButton("Graphics", []() { switchPanel(graphicsPanel.get()); });
	settingsPanel->addButton("Back", []() { switchPanel(menuPanel.get()); });
	settingsPanel->setVisible(false);

	// Graphics
	graphics.swap(makeEntity());
	graphics->setPosition(sf::Vector2f(GAMEX / 2, GAMEY / 2 + 96.0f));
	graphicsPanel.swap(graphics->addComponent<PanelComponent>(sf::Vector2f(0.5f, 0.5f), 96.0f));
	graphicsPanel->addText("Graphics", 48.0f);
	graphicsPanel->addButton("1920x1080", []() { Engine::getWindow().setSize(sf::Vector2u(1920, 1080)); UpdateScaling(); });
	graphicsPanel->addButton("1600x900", []() { Engine::getWindow().setSize(sf::Vector2u(1600, 900)); UpdateScaling(); });
	graphicsPanel->addButton("1280x720", []() { Engine::getWindow().setSize(sf::Vector2u(1280, 720)); UpdateScaling(); });
	graphicsPanel->addButton("Window Mode", []() { Engine::switchWindowMode(); UpdateScaling(); });
	graphicsPanel->addButton("Back", []() { Files::saveSettings(); switchPanel(settingsPanel.get()); });
	graphicsPanel->setVisible(false);

	// Controls
	controls.swap(makeEntity());
	controls->setPosition(sf::Vector2f(GAMEX / 2, GAMEY / 2 + 96.0f));
	controlsPanel.swap(controls->addComponent<PanelComponent>(sf::Vector2f(0.5f, 0.5f), 96.0f));
	controlsPanel->addButton(
		[]() -> std::string { return "Thrust/Up: " + Input::keys[Input::KeyCode::P1_THRUST].second; },
		[]() { Input::keys[Input::KeyCode::P1_THRUST].second = "";
				changeKeyCode = Input::KeyCode::P1_THRUST;
	});
	controlsPanel->addButton(
		[]() -> std::string { return "Down: " + Input::keys[Input::KeyCode::P1_DOWN].second; },
		[]() { Input::keys[Input::KeyCode::P1_DOWN].second = "";
				changeKeyCode = Input::KeyCode::P1_DOWN;
	});
	controlsPanel->addButton(
		[]() -> std::string { return "Left: " + Input::keys[Input::KeyCode::P1_LEFT].second; },
		[]() { Input::keys[Input::KeyCode::P1_LEFT].second = "";
				changeKeyCode = Input::KeyCode::P1_LEFT;
	});
	controlsPanel->addButton(
		[]() -> std::string { return "Right: " + Input::keys[Input::KeyCode::P1_RIGHT].second; },
		[]() { Input::keys[Input::KeyCode::P1_RIGHT].second = "";
				changeKeyCode = Input::KeyCode::P1_RIGHT;
	});
	controlsPanel->addButton(
		[]() -> std::string { return "Shoot: " + Input::keys[Input::KeyCode::P1_FIRE].second; },
		[]() { Input::keys[Input::KeyCode::P1_FIRE].second = "";
				changeKeyCode = Input::KeyCode::P1_FIRE;
	});
	controlsPanel->addButton("Back", []() { Files::saveControls(); switchPanel(settingsPanel.get()); });
	controlsPanel->setVisible(false);

	// Highscores
	high.swap(makeEntity());
	high->setPosition(sf::Vector2f(GAMEX / 2, GAMEY / 2 + 64.0f));
	highscoresPanel.swap(high->addComponent<PanelComponent>(sf::Vector2f(0.5f, 0.5f), 38.0f));
	highscoresPanel->addText("High Scores", 48.0f);
	highscoresPanel->addText("", 8.0f);
	// Adding highscores
	if (highscores.size() == 0)
	{
		// Add text to indicate that there's no highscores so far
		highscoresPanel->addText("No high scores!", 32.0f);
	}
	else
	{
		// Display highscores
		for(auto it = highscores.rbegin(); it != highscores.rend(); ++it)
			highscoresPanel->addText(it->second + "\t" + std::to_string(it->first), 32.0f);
	}
	// Add empty text to fit the back button
	highscoresPanel->addText("");
	highscoresPanel->addButton("Back", []() { switchPanel(menuPanel.get()); });
	highscoresPanel->setVisible(false);

	// Load graphics settings
	if (!Files::loadSettings())
		switchWindow = true;
	UpdateScaling();
	setLoaded(true);
}

void MenuScene::onKeyPressed(std::variant<Keyboard::Key, unsigned int> k)
{
	if (!menuScene.isLoaded())
		return;

	Keyboard::Key keyboardKey = Keyboard::Unknown;
	unsigned int joystickButton = 0;

	// Keyboard
	if (std::holds_alternative<Keyboard::Key>(k))
		keyboardKey = std::get<Keyboard::Key>(k);
	// Joystick
	else
		joystickButton = std::get<unsigned int>(k);

	// Changing player controls
	if (changeKeyCode != (Input::KeyCode)-1)
	{
		// Keyboard
		if (keyboardKey != Keyboard::Unknown)
		{
			Input::keys[changeKeyCode].first = keyboardKey;

			// Handling some keys that don't trigger TextEntered event or don't return key names
			switch (keyboardKey)
			{
			case Keyboard::Space: Input::keys[changeKeyCode].second = "Space"; break;
			case Keyboard::Up: Input::keys[changeKeyCode].second = "Up"; break;
			case Keyboard::Down: Input::keys[changeKeyCode].second = "Down"; break;
			case Keyboard::Left: Input::keys[changeKeyCode].second = "Left"; break;
			case Keyboard::Right: Input::keys[changeKeyCode].second = "Right"; break;
			case Keyboard::Enter: Input::keys[changeKeyCode].second = "Enter"; break;
			case Keyboard::LControl: Input::keys[changeKeyCode].second = "LControl"; break;
			case Keyboard::RControl: Input::keys[changeKeyCode].second = "RControl"; break;
			case Keyboard::LAlt: Input::keys[changeKeyCode].second = "LAlt"; break;
			case Keyboard::RAlt: Input::keys[changeKeyCode].second = "RAlt"; break;
			default: changeTextEntered = changeKeyCode; break;
			}
		}
		// Joystick
		else
		{
			Input::keys[changeKeyCode].first = joystickButton;
			Input::keys[changeKeyCode].second = std::to_string(joystickButton);
		}
		
		changeKeyCode = (Input::KeyCode)-1;

		return;
	}

	// Menu navigation
	if (std::holds_alternative<unsigned int>(k))
		return;

	if (keyboardKey == Keyboard::Up)
	{
		currentPanel->pointerPrevious();
	}
	else if (keyboardKey == Keyboard::Down)
	{	
		currentPanel->pointerNext();
	}
	else if (keyboardKey == Keyboard::Enter)
	{	
		currentPanel->executeButton();
	}

}

void MenuScene::onTextEntered(std::string text)
{
	if (!menuScene.isLoaded())
		return;

	if (changeTextEntered != (Input::KeyCode)-1)
	{
		Input::keys[changeTextEntered].second = text;
		changeTextEntered = (Input::KeyCode) - 1;
	}
}

void MenuScene::update(const double& dt) {
  
	if (switchWindow)
	{
		Engine::switchWindowMode();
		UpdateScaling();
		switchWindow = false;
	}
	Scene::update(dt);
}

// Switch scene to menu safely
void MenuScene::gotoGame()
{
	// Resetting all shared_ptr
	txtTitle.reset();

	menuPanel.reset();
	menu->setForDelete();

	settingsPanel.reset();
	settings->setForDelete();

	graphicsPanel.reset();
	graphics->setForDelete();

	controlsPanel.reset();
	controls->setForDelete();

	highscoresPanel.reset();
	high->setForDelete();

	currentPanel = nullptr;

	Engine::changeScene(&gameScene);
}