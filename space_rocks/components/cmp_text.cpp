#include "cmp_text.h"
#include <system_renderer.h>
#include <system_resources.h>

void TextComponent::update(double dt) {

	sf::FloatRect bounds = _text.getLocalBounds();
	
	//Position
	_text.setPosition(sf::Vector2f(
		_parent->getPosition().x - _anchor.x * bounds.width,
		_parent->getPosition().y - _anchor.y * bounds.height));
}

void TextComponent::render() { Renderer::queue(&_text); }

TextComponent::TextComponent(Entity* const p, const std::string& str)
    : Component(p), _string(str) {
  _text.setString(_string);
  _font = Resources::get<sf::Font>("Acuter.ttf");
  _text.setFont(*_font);
  _anchor = sf::Vector2f(0.5f, 0.5f);
}

void TextComponent::SetText(const std::string& str) {
  _string = str;
  _text.setString(_string);
}

// Set anchor:
// 0.0, 0.0	= top left
// 0.5, 0.5	= center
// 1.0, 1.0	= bottom right
// Values outside of this range will be rounded to closest edge
void TextComponent::SetAnchor(sf::Vector2f vec)
{
	//Inforce limits
	vec.x = vec.x < 0.0f ? 0.0f : vec.x;
	vec.x = vec.x > 1.0f ? 1.0f : vec.x;
	vec.y = vec.y < 0.0f ? 0.0f : vec.y;
	vec.y = vec.y > 1.0f ? 1.0f : vec.y;

	_anchor = vec;
}

//Set character size in pixels
void TextComponent::SetSize(unsigned int size)
{
	_text.setCharacterSize(size);
}
