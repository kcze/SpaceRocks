#include "cmp_text.h"
#include <system_renderer.h>
#include <system_resources.h>

void TextComponent::update(double dt) {

	sf::FloatRect bounds = _text.getLocalBounds();
	
	switch (_alignment)
	{
	//Left Edge
	case -1: 
		_text.setPosition(_parent->getPosition());
		break;
	//Center
	case 0 : 
		_text.setPosition(sf::Vector2f(_parent->getPosition().x - bounds.width / 2, _parent->getPosition().y));
		break;
	//Right Edge
	case 1 : 
		_text.setPosition(sf::Vector2f(_parent->getPosition().x - bounds.width, _parent->getPosition().y));
		break;
	}
}

void TextComponent::render() { Renderer::queue(&_text); }

TextComponent::TextComponent(Entity* const p, const std::string& str)
    : Component(p), _string(str) {
  _text.setString(_string);
  _font = Resources::get<sf::Font>("Acuter.ttf");
  _text.setFont(*_font);
  _alignment = 0;
}

void TextComponent::SetText(const std::string& str) {
  _string = str;
  _text.setString(_string);
}

// Set text alignment (anchor position): 
// -1 = Left Edge, 0 = Center, 1 = Right Edge
void TextComponent::SetAlignment(int i)
{
	if (i >= -1 && i <= 1)
		_alignment = i;
}