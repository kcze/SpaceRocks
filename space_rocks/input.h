#pragma once
#include <list>
#include <SFML/Window.hpp>
#include <map>

using namespace sf;

class InputEvents;

class Input {
	friend class InputEvents;

public:
	enum KeyCode {
		P1_LEFT,
		P1_RIGHT,
		P1_THRUST,
		P1_FIRE
	};

	static std::map<Input::KeyCode, Keyboard::Key> keys;

	static bool isKeyPressed(Keyboard::Keyboard::Key key);
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

};

class InputEvents {
public:
	InputEvents() { Input::registerHandler(this); }

	virtual void onKeyPressed(Keyboard::Keyboard::Key key) {}
	virtual void onKeyReleased(Keyboard::Keyboard::Key key) {}
	virtual void onKey(Keyboard::Keyboard::Key key) {}
	virtual void onMousePressed(Mouse::Button button) {}
	virtual void onMouseReleased(Mouse::Button button) {}
	virtual void onMouse(Mouse::Button button) {}
	virtual void onMouseMove(int x, int y) {}
	virtual void onResize(int x, int y) {}

	virtual ~InputEvents() { Input::unregisterHandler(this); }
};