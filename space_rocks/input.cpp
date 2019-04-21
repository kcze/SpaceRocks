#include "input.h"
#include <iostream>

std::map<Input::KeyCode, std::pair<std::variant<Keyboard::Key, unsigned int>, std::string>> Input::keys =
{
	{ KeyCode::P1_LEFT, { Keyboard::Key::Left, "Left" } },
	{ KeyCode::P1_RIGHT, { Keyboard::Key::Right, "Right" }  },
	{ KeyCode::P1_THRUST, { Keyboard::Key::Up, "Up" } },
	{ KeyCode::P1_DOWN, { Keyboard::Key::Down, "Down" } },
	{ KeyCode::P1_FIRE, { Keyboard::Key::Space, "Space" } }
};

std::list<void(*)(std::variant<Keyboard::Key, unsigned int>)>		Input::keyPressedHandlers;
std::list<void(*)(std::variant<Keyboard::Key, unsigned int>)>		Input::keyReleasedHandlers;
//std::list<void(*)(std::variant<Keyboard::Key, unsigned int>)>		Input::keyHandlers;
std::list<void(*)(Mouse::Button)>	Input::mousePressedHandlers;
std::list<void(*)(Mouse::Button)>	Input::mouseReleasedHandlers;
std::list<void(*)(Mouse::Button)>	Input::mouseHandlers;
std::list<void(*)(int, int)>		Input::mouseMoveHandlers;
std::list<void(*)(int, int)>		Input::resizeHandlers;
std::list<void(*)(std::string)>		Input::textEnteredHandlers;
std::list<InputEvents*>				Input::handlers;

std::variant<Keyboard::Key, unsigned int> Input::lastKey = Keyboard::Key::Unknown;//todo change to vector
Mouse::Button Input::lastButton = (sf::Mouse::Button)-1;//todo change to vector
Vector2f Input::lastMousePos;

void Input::init() { }

Input::KeyCode Input::getKeyCode(std::variant<Keyboard::Key, unsigned int> key) {
	std::map<Input::KeyCode, std::pair<std::variant<Keyboard::Key, unsigned int>, std::string>>::iterator iterator = Input::keys.begin();

	while (iterator != Input::keys.end())
	{
		if (key == iterator->second.first)
			return iterator->first;

		iterator++;
	}

	return Input::KeyCode::NONE;
}

bool Input::isKeyPressed(std::variant<Keyboard::Key, unsigned int> key) {
	if (std::holds_alternative<Keyboard::Key>(key))
		return sf::Keyboard::isKeyPressed(std::get<Keyboard::Key>(key));
	else
		return sf::Joystick::isButtonPressed(0, std::get<unsigned int>(key));
}

bool Input::isKeyReleased(std::variant<Keyboard::Key, unsigned int> key) {
	if (std::holds_alternative<Keyboard::Key>(key))
		return !sf::Keyboard::isKeyPressed(std::get<Keyboard::Key>(key));
	else
		return !sf::Joystick::isButtonPressed(0, std::get<unsigned int>(key));
}

bool Input::isMousePressed(Mouse::Button button) { return  sf::Mouse::isButtonPressed((sf::Mouse::Button)button); }
bool Input::isMouseReleased(Mouse::Button button) { return !sf::Mouse::isButtonPressed((sf::Mouse::Button)button); }

bool Input::isKeyDown(Input::KeyCode keyCode) {
	std::map<Input::KeyCode, std::pair<std::variant<Keyboard::Key, unsigned int>, std::string>>::iterator iterator = Input::keys.find(keyCode);
	
	// Mapping wasn't found
	if (iterator == Input::keys.end())
		return false;

	if (std::holds_alternative<Keyboard::Key>(iterator->second.first))
		return Input::isKeyPressed(std::get<Keyboard::Key>(iterator->second.first));
	else
		return Input::isKeyPressed(std::get<unsigned int>(iterator->second.first));
}

bool Input::isKeyUp(Input::KeyCode keyCode) {
	std::map<Input::KeyCode, std::pair<std::variant<Keyboard::Key, unsigned int>, std::string>>::iterator iterator = Input::keys.find(keyCode);

	// Mapping wasn't found
	if (iterator == Input::keys.end())
		return false;

	if(std::holds_alternative<Keyboard::Key>(iterator->second.first))
		return Input::isKeyReleased(std::get<Keyboard::Key>(iterator->second.first));
	else
		return Input::isKeyReleased(std::get<unsigned int>(iterator->second.first));
}


Vector2f Input::mousePosition() {
	//todo not implemented
	//Vector2f pos = sf::Mouse::getPosition(WINDOW);
	
	return Vector2f(0.0f, 0.0f);
}

void Input::onKeyPressed(sf::Event event) {
	// Keyboard
	if (event.type == sf::Event::KeyPressed)
	{
		if (std::holds_alternative<Keyboard::Key>(lastKey))
			if (std::get<Keyboard::Key>(lastKey) == (Keyboard::Key)event.key.code)
				return;

		lastKey = (Keyboard::Key)event.key.code;
		for (auto func : keyPressedHandlers) func((Keyboard::Key)event.key.code);
		for (auto handler : handlers) handler->onKeyPressed((Keyboard::Key)event.key.code);
	}
	// Joystick
	else if (event.type == sf::Event::JoystickButtonPressed)
	{
		if (std::holds_alternative<unsigned int>(lastKey))
			if (std::get<unsigned int>(lastKey) == event.joystickButton.button)
				return;

		lastKey = event.joystickButton.button;
		for (auto func : keyPressedHandlers) func(event.joystickButton.button);
		for (auto handler : handlers) handler->onKeyPressed(event.joystickButton.button);
	}
}

void Input::onKeyReleased(sf::Event event) {
	// Keyboard
	if (event.type == sf::Event::KeyReleased)
	{
		if (std::holds_alternative<Keyboard::Key>(lastKey))
			if (std::get<Keyboard::Key>(lastKey) == (Keyboard::Key)event.key.code)
				lastKey = Keyboard::Key::Unknown;

		for (auto func : keyReleasedHandlers) func((Keyboard::Key)event.key.code);
		for (auto handler : handlers) handler->onKeyReleased((Keyboard::Key)event.key.code);
	}
	// Joystick
	else if (event.type == sf::Event::JoystickButtonReleased)
	{
		if (std::holds_alternative<unsigned int>(lastKey))
			if (std::get<unsigned int>(lastKey) == event.joystickButton.button)
				lastKey = (unsigned int)0;

		for (auto func : keyReleasedHandlers) func(event.joystickButton.button);
		for (auto handler : handlers) handler->onKeyReleased(event.joystickButton.button);
	}
	//todo useless
	/*if (std::get<Keyboard::Key>(lastKey) == (Keyboard::Key)event.key.code) {
		lastKey = Keyboard::Key::Unknown;
		for (auto func : keyHandlers) func((Keyboard::Key)event.key.code);
		for (auto handler : handlers) handler->onKey((Keyboard::Key)event.key.code);
	}*/
}

void Input::onMousePressed(sf::Event event) {
	if (lastButton != (Mouse::Button)event.mouseButton.button) {
		lastButton = (Mouse::Button)event.mouseButton.button;
		lastMousePos = mousePosition();
		for (auto func : mousePressedHandlers) func((Mouse::Button)event.mouseButton.button);
		for (auto handler : handlers) handler->onMousePressed((Mouse::Button)event.mouseButton.button);
	}
}

void Input::onMouseReleased(sf::Event event) {
	for (auto func : mouseReleasedHandlers) func((Mouse::Button)event.mouseButton.button);
	for (auto handler : handlers) handler->onMouseReleased((Mouse::Button)event.mouseButton.button);

	if (lastButton == (Mouse::Button)event.mouseButton.button && lastMousePos == mousePosition()) {
		for (auto func : mouseHandlers) func((Mouse::Button)event.mouseButton.button);
		for (auto handler : handlers) handler->onMouse((Mouse::Button)event.mouseButton.button);
	}

	lastButton = (sf::Mouse::Button)-1;
	lastMousePos = Vector2f(-1, -1);
}

void Input::onMouseMoved(sf::Event event) {
	for (auto func : mouseMoveHandlers) { Vector2f pos = mousePosition(); func(pos.x, pos.y); }
	for (auto handler : handlers) { Vector2f pos = mousePosition(); handler->onMouseMove(pos.x, pos.y); }
}

void Input::onResized(sf::Event event) {
	for (auto func : resizeHandlers) func(event.size.width, event.size.height);
	for (auto handler : handlers) handler->onResize(event.size.width, event.size.height);
	//todo refresh window
}

void Input::onTextEntered(sf::Event event) {
	std::string str = ((sf::String)(event.text.unicode)).toAnsiString();

	for (auto func : textEnteredHandlers) func(str);
	for (auto handler : handlers) handler->onTextEntered(str);
}

void Input::keyPressed(void(*handler)(std::variant<Keyboard::Key, unsigned int>)) { keyPressedHandlers.push_back(handler); }
void Input::keyReleased(void(*handler)(std::variant<Keyboard::Key, unsigned int>)) { keyReleasedHandlers.push_back(handler); }
//void Input::key(void(*handler)(std::variant<Keyboard::Key, unsigned int>)) { keyHandlers.push_back(handler); }
void Input::mousePressed(void(*handler)(Mouse::Button)) { mousePressedHandlers.push_back(handler); }
void Input::mouseReleased(void(*handler)(Mouse::Button)) { mouseReleasedHandlers.push_back(handler); }
void Input::mouse(void(*handler)(Mouse::Button)) { mouseHandlers.push_back(handler); }
void Input::mouseMove(void(*handler)(int, int)) { mouseMoveHandlers.push_back(handler); }
void Input::resize(void(*handler)(int, int)) { resizeHandlers.push_back(handler); }
void Input::textEntered(void(*handler)(std::string)) { textEnteredHandlers.push_back(handler); }

void Input::registerHandler(InputEvents* handler) { handlers.push_back(handler); }
void Input::unregisterHandler(InputEvents* handler) { handlers.remove(handler); }