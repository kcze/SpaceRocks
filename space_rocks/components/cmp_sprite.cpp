#include "cmp_sprite.h"
#include "system_renderer.h"

using namespace std;

// Sprite
void SpriteComponent::setTexure(std::shared_ptr<sf::Texture> tex)
{
  _texture = tex;
  _sprite->setTexture(*_texture);
}

void SpriteComponent::setTextureRect(sf::IntRect rect)
{
	_sprite->setTextureRect(rect);
}

void SpriteComponent::setOrigin(const sf::Vector2f origin)
{
	_sprite->setOrigin(origin);
}

SpriteComponent::SpriteComponent(Entity* p)
    : Component(p), _sprite(make_shared<sf::Sprite>()) {}

void SpriteComponent::update(double dt) {
  _sprite->setPosition(_parent->getPosition());
  _sprite->setRotation(_parent->getRotation());
}

void SpriteComponent::render() { Renderer::queue(_sprite.get()); }


// Shape
void ShapeComponent::update(double dt) {
	sf::FloatRect bounds = _shape->getLocalBounds();

	//Position
	_shape->setPosition(sf::Vector2f(
		_parent->getPosition().x - _anchor.x * bounds.width,
		_parent->getPosition().y - _anchor.y * bounds.height));

	_shape->setRotation(_parent->getRotation());
}

void ShapeComponent::render() { Renderer::queue(_shape.get()); }

sf::Shape& ShapeComponent::getShape() const { return *_shape; }

ShapeComponent::ShapeComponent(Entity* p)
	: Component(p), _shape(make_shared<sf::CircleShape>()) {
	_anchor = sf::Vector2f(0.5f, 0.5f);
}

sf::Sprite& SpriteComponent::getSprite() const { return *_sprite; }

// Set anchor:
// 0.0, 0.0	= top left
// 0.5, 0.5	= center
// 1.0, 1.0	= bottom right
// Values outside of this range will be rounded to closest edge
void ShapeComponent::SetAnchor(sf::Vector2f vec)
{
	//Inforce limits
	vec.x = vec.x < 0.0f ? 0.0f : vec.x;
	vec.x = vec.x > 1.0f ? 1.0f : vec.x;
	vec.y = vec.y < 0.0f ? 0.0f : vec.y;
	vec.y = vec.y > 1.0f ? 1.0f : vec.y;

	_anchor = vec;
}
