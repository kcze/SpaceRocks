#pragma once
#include <list>
#include <SFML/Window.hpp>
#include <map>
#include "engine.h"

using namespace sf;

class InputEvents;

class Input {
	friend class InputEvents;
	friend class Engine;

public:
	enum KeyCode {
		P1_LEFT,
		P1_RIGHT,
		P1_THRUST,
		P1_FIRE
	};

	static std::map<Input::KeyCode, std::pair<Keyboard::Key, std::string>> keys;

	static bool isKeyPressed(Keyboard::Key key);
	static bool isKeyReleased(Keyboard::Key key);
	static bool isMousePressed(Mouse::Button button);
	static bool isMouseReleased(Mouse::Button button);

	//todo could use union -> one method for KeyCode, Keyboard::Key
	static bool isKeyDown(KeyCode keyCode);
	static bool isKeyUp(KeyCode keyCode);

	static Vector2f mousePosition();

	static void keyPressed(void(*handler)(Keyboard::Key));
	static void keyReleased(void(*handler)(Keyboard::Key));
	static void key(void(*handler)(Keyboard::Key));
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

	static std::list<void(*)(Keyboard::Key)>		keyPressedHandlers;
	static std::list<void(*)(Keyboard::Key)>		keyReleasedHandlers;
	static std::list<void(*)(Keyboard::Key)>		keyHandlers;
	static std::list<void(*)(Mouse::Button)>	mousePressedHandlers;
	static std::list<void(*)(Mouse::Button)>	mouseReleasedHandlers;
	static std::list<void(*)(Mouse::Button)>	mouseHandlers;
	static std::list<void(*)(int, int)>	mouseMoveHandlers;
	static std::list<void(*)(int, int)>	resizeHandlers;
	static std::list<void(*)(std::string)>		textEnteredHandlers;
	static std::list<InputEvents*>		handlers;

	static Keyboard::Key lastKey;
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

	virtual void onKeyPressed(Keyboard::Key key) {}
	virtual void onKeyReleased(Keyboard::Key key) {}
	virtual void onKey(Keyboard::Key key) {}
	virtual void onMousePressed(Mouse::Button button) {}
	virtual void onMouseReleased(Mouse::Button button) {}
	virtual void onMouse(Mouse::Button button) {}
	virtual void onMouseMove(int x, int y) {}
	virtual void onResize(int x, int y) {}
	virtual void onTextEntered(std::string text) {}

	virtual ~InputEvents() { Input::unregisterHandler(this); }
};