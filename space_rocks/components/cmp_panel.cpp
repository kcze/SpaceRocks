#include "cmp_panel.h"
#include "..\game.h"
#include "system_resources.h"
#include <vector>
#include <iterator>

PanelComponent::PanelComponent(Entity* const p, const sf::Vector2f anchor, const float interval)
	: Component(p), _anchor(anchor), _interval(interval) {

	_panelScene = Engine::getActiveScene();
	// Create and hide button pointer
	_buttonPointer = _panelScene->makeEntity();
	auto spr = _buttonPointer->addComponent<SpriteComponent>();
	spr->setTextureRect(sf::IntRect(0, 96, 256, 96));
	spr->setTexure(Resources::load<sf::Texture>("button.png"));
	_buttonPointer->setVisible(false);
}

PanelComponent::~PanelComponent() { }

void PanelComponent::update(double dt) { }

void PanelComponent::addButton(const std::string text, std::function<void()> function) {

	// Create text for the button
	auto button = addText(text);

	// Create frame
	auto frame = button->addComponent<SpriteComponent>();
	frame->setTextureRect(sf::IntRect(0, 0, 256, 96));
	frame->setTexure(Resources::load<sf::Texture>("button.png"));

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
}

std::shared_ptr<Entity> PanelComponent::addText(const std::string text, const float size) {

	std::shared_ptr<Entity> entity = _panelScene->makeEntity();
	auto txt = entity->addComponent<TextComponent>(text);
	txt->setSize(size);
	txt->setAnchor(_anchor);

	_elements.push_back(entity);

	updatePositions();

	return entity;
}

std::shared_ptr<Entity> PanelComponent::addText(std::function<std::string()> function, const float size) {

	std::shared_ptr<Entity> entity = _panelScene->makeEntity();
	auto txt = entity->addComponent<TextComponent>("");
	txt->setSize(size);
	txt->setAnchor(_anchor);

	// Create ui component
	auto ui = entity->addComponent<UiComponent>();
	ui->textUpdate = function;

	_elements.push_back(entity);

	updatePositions();

	return entity;
}

void PanelComponent::executeButton()
{
	if (_currentButton != NULL)
		_currentButton->getComponents<UiComponent>()[0]->buttonExecute();
}

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

	updatePositions();
}

void PanelComponent::pointerNext()
{
	if (_buttons.size() < 2)
		return;

	if (_currentButton == _buttons.back())
		_currentButton = _buttons.front();
	else
	{
		/*std::vector<std::shared_ptr<Entity>>::iterator it = std::find(_buttons.begin(), _buttons.end(), _currentButton);

		int i = std::distance(_buttons.begin(), it);

		_currentButton = _buttons.at(i + 1);//*/

		for (int i = 0; i < _buttons.size(); i++)
		{
			if (_currentButton == _buttons[i])
			{
				_currentButton = _buttons[i + 1];
				break;
			}
		}
	}

	updatePositions();
}

void PanelComponent::updatePositions()
{
	if (_elements.size() == 0)
		return;

	sf::Vector2f center = _parent->getPosition();
	int size = _elements.size();

	// Placing entities vertically
	for (int i = 0; i < size; i++)
	{
		_elements[i]->setPosition(sf::Vector2f(center.x, center.y - (size / 2.0f) * _interval + i * _interval));
	}

	// Setting position for button pointer
	if (_currentButton != NULL)
		_buttonPointer->setPosition(_currentButton->getPosition());

}