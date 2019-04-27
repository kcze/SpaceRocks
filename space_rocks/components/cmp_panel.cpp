#include "cmp_panel.h"
#include "cmp_destructible.h"
#include "..\game.h"
#include "system_resources.h"
#include <vector>
#include <iterator>

PanelComponent::PanelComponent(Entity* const p, const sf::Vector2f anchor, const float interval, const bool horizontal)
	: Component(p), _anchor(anchor), _interval(interval), _horizontal(horizontal) {

	_panelScene = Engine::getActiveScene();
	_visible = true;
	// Create and hide button pointer
	_buttonPointer = _panelScene->makeEntity();
	auto spr = _buttonPointer->addComponent<SpriteComponent>();
	spr->setTextureRect(sf::IntRect(0, 96, 256, 96));
	spr->setTexure(Resources::get<sf::Texture>("button.png"));
	_buttonPointer->setVisible(false);
}

PanelComponent::~PanelComponent() { 
	_buttonPointer.reset();
	_currentButton.reset();
	
	for (auto p : _buttons)
		p.reset();

	for (auto p : _elements)
		p.reset();
}

void PanelComponent::update(double dt) { }

// Adds a button
void PanelComponent::addButton(const std::string text, std::function<void()> function) {

	// Create text for the button
	auto button = addText(text);

	// Create frame
	auto frame = button->addComponent<SpriteComponent>();
	frame->setTextureRect(sf::IntRect(0, 0, 256, 96));
	frame->setTexure(Resources::get<sf::Texture>("button.png"));

	// Create ui component
	auto ui = button->addComponent<UiComponent>();
	ui->buttonExecute = function;
	
	// Set button pointer
	if (_currentButton == NULL)
	{
		_currentButton = button;
		_buttonPointer->setVisible(true);
	}

	_buttons.push_back(button);
	updatePositions();
}

// Adds a button with dynamic text
void PanelComponent::addButton(std::function<std::string()> text, std::function<void()> function) {

	// Create text for the button
	auto button = addText(text);

	// Create frame
	auto frame = button->addComponent<SpriteComponent>();
	frame->setTextureRect(sf::IntRect(0, 0, 256, 96));
	frame->setTexure(Resources::get<sf::Texture>("button.png"));

	// Create ui component
	if (button->getComponents<UiComponent>().size() == 0)
	{
		auto ui = button->addComponent<UiComponent>();
		ui->buttonExecute = function;
	}
	else
	{
		button->getComponents<UiComponent>()[0]->buttonExecute = function;
	}

	// Set button pointer
	if (_currentButton == NULL)
	{
		_currentButton = button;
		_buttonPointer->setVisible(true);
	}

	_buttons.push_back(button);
	updatePositions();
}

// Adds text
std::shared_ptr<Entity> PanelComponent::addText(const std::string text, const float size) {

	std::shared_ptr<Entity> entity = _panelScene->makeEntity();
	auto txt = entity->addComponent<TextComponent>(text);
	txt->setSize(size);
	txt->setAnchor(_anchor + sf::Vector2f(0.0f, 0.1f));

	_elements.push_back(entity);
	updatePositions();

	return entity;
}

// Adds dynamic text
std::shared_ptr<Entity> PanelComponent::addText(std::function<std::string()> function, const float size) {

	std::shared_ptr<Entity> entity = _panelScene->makeEntity();
	auto txt = entity->addComponent<TextComponent>("");
	txt->setSize(size);
	txt->setAnchor(_anchor + sf::Vector2f(0.0f, 0.1f));

	// Create ui component
	auto ui = entity->addComponent<UiComponent>();
	ui->textUpdate = function;

	_elements.push_back(entity);
	updatePositions();

	return entity;
}

// Executes a function associated with currently selected button
void PanelComponent::executeButton()
{
	if (_currentButton != NULL)
	{
		_currentButton->getComponents<UiComponent>()[0]->buttonExecute();
		audioManager.playSound("menu_select");
	}

}

// Moves pointer to a previous button
void PanelComponent::pointerPrevious()
{
	if (_buttons.size() < 2)
		return;
	
	if (_currentButton == _buttons.front())
		_currentButton = _buttons.back();
	else
	{
		for (int i = _buttons.size() - 1; i > 0 ; i--)
		{
			if (_currentButton == _buttons[i])
			{
				_currentButton = _buttons[i - 1];
				break;
			}
		}
	}
	audioManager.playSound("menu_cycle");
	updatePositions();
}

// Moves pointer to a next button
void PanelComponent::pointerNext()
{
	if (_buttons.size() < 2)
		return;

	if (_currentButton == _buttons.back())
		_currentButton = _buttons.front();
	else
	{
		for (int i = 0; i < _buttons.size(); i++)
		{
			if (_currentButton == _buttons[i])
			{
				_currentButton = _buttons[i + 1];
				break;
			}
		}
	}
	audioManager.playSound("menu_cycle");
	updatePositions();
}

// Places all elements properly
void PanelComponent::updatePositions()
{
	if (_elements.size() == 0)
		return;

	sf::Vector2f center = _parent->getPosition();
	int size = _elements.size();

	// Placing entities
	for (int i = 0; i < size; i++)
	{
		if(_horizontal)
			_elements[i]->setPosition(sf::Vector2f(center.x - (size / 2.0f) * _interval + i * _interval, center.y));
		else
			_elements[i]->setPosition(sf::Vector2f(center.x, center.y - (size / 2.0f) * _interval + i * _interval));
	}

	// Setting position for button pointer
	if (_currentButton != NULL)
		_buttonPointer->setPosition(_currentButton->getPosition());

}

// Hides or displays all elements
void PanelComponent::setVisible(bool visible)
{
	_visible = visible;
	// Hide or expose all elements in the panel
	for (std::shared_ptr<Entity> element : _elements)
	{
		element->setVisible(visible);
		element->setAlive(visible);
	}
	if (_buttonPointer != NULL)
	{
		_buttonPointer->setVisible(visible);
		_buttonPointer->setAlive(visible);
	}
}