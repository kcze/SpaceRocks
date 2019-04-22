#pragma once
#include <list>
#include <SFML/Window.hpp>
#include <map>
#include <variant>
#include "engine.h"

constexpr auto AXIS_THRESHOLD = 50;

using namespace sf;

class InputEvents;

class Input {
	friend class InputEvents;
	friend class Engine;

public:
	enum KeyCode {
		NONE,
		P1_LEFT,
		P1_RIGHT,
		P1_THRUST,
		P1_DOWN,
		P1_FIRE
	};
	
	static std::map<Input::KeyCode, std::pair<std::variant<Keyboard::Key, unsigned int>, std::string>> keys;

	static Input::KeyCode getKeyCode(std::variant<Keyboard::Key, unsigned int> key);

	static bool isKeyPressed(std::variant<Keyboard::Key, unsigned int> key);
	static bool isKeyReleased(std::variant<Keyboard::Key, unsigned int> key);
	static bool isMousePressed(Mouse::Button button);
	static bool isMouseReleased(Mouse::Button button);

	static bool isKeyDown(KeyCode keyCode);
	static bool isKeyUp(KeyCode keyCode);

	static Vector2f mousePosition();

	static void keyPressed(void(*handler)(std::variant<Keyboard::Key, unsigned int>));
	static void keyReleased(void(*handler)(std::variant<Keyboard::Key, unsigned int>));
	//static void key(void(*handler)(std::variant<Keyboard::Key, unsigned int>));
	static void mousePressed(void(*handler)(Mouse::Button));
	static void mouseReleased(void(*handler)(Mouse::Button));
	static void mouse(void(*handler)(Mouse::Button));
	static void mouseMove(void(*handler)(int, int));
	static void resize(void(*handler)(int, int));
	static void textEntered(void(*handler)(std::string));

private:
	Input() {} // Static class

	static void registerHandler(InputEvents* handler);
	static void unregisterHandler(InputEvents* handler);

	static std::list<void(*)(std::variant<Keyboard::Key, unsigned int>)>		keyPressedHandlers;
	static std::list<void(*)(std::variant<Keyboard::Key, unsigned int>)>		keyReleasedHandlers;
	//static std::list<void(*)(std::variant<Keyboard::Key, unsigned int>)>		keyHandlers;
	static std::list<void(*)(Mouse::Button)>	mousePressedHandlers;
	static std::list<void(*)(Mouse::Button)>	mouseReleasedHandlers;
	static std::list<void(*)(Mouse::Button)>	mouseHandlers;
	static std::list<void(*)(int, int)>	mouseMoveHandlers;
	static std::list<void(*)(int, int)>	resizeHandlers;
	static std::list<void(*)(std::string)>		textEnteredHandlers;
	static std::list<InputEvents*>		handlers;

	static std::variant<Keyboard::Key, unsigned int> lastKey;
	static Mouse::Button lastButton;
	static Vector2f lastMousePos;

	static void init();

	static void onKeyPressed(sf::Event event);
	static void onKeyReleased(sf::Event event);
	static void onMousePressed(sf::Event event);
	static void onMouseReleased(sf::Event event);
	static void onMouseMoved(sf::Event event);
	static void onResized(sf::Event event);
	static void onTextEntered(sf::Event event);

};

class InputEvents {
public:
	InputEvents() { Input::registerHandler(this); }

	virtual void onKeyPressed(std::variant<Keyboard::Key, unsigned int> key) {}
	virtual void onKeyReleased(std::variant<Keyboard::Key, unsigned int> key) {}
	//virtual void onKey(std::variant<Keyboard::Key, unsigned int> key) {}
	virtual void onMousePressed(Mouse::Button button) {}
	virtual void onMouseReleased(Mouse::Button button) {}
	virtual void onMouse(Mouse::Button button) {}
	virtual void onMouseMove(int x, int y) {}
	virtual void onResize(int x, int y) {}
	virtual void onTextEntered(std::string text) {}

	virtual ~InputEvents() { Input::unregisterHandler(this); }
};