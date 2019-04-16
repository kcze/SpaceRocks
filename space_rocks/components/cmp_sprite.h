#pragma once

#include "ecm.h"
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>

// Sprite
class SpriteComponent : public Component {
protected:
  std::shared_ptr<sf::Sprite> _sprite;
  std::shared_ptr<sf::Texture> _texture;
  sf::Vector2f _anchor;
  bool _draw;

public:
  SpriteComponent() = delete;

  void SpriteComponent::setAnchor(sf::Vector2f vec);

  explicit SpriteComponent(Entity* p);
  void update(double dt) override;
  void render() override;

  sf::Sprite& getSprite() const;

  void setTexure(std::shared_ptr<sf::Texture> tex);
  void setTextureRect(sf::IntRect);
  void setOrigin(const sf::Vector2f origin);
  void setDraw(bool draw);
};

// Shape
class ShapeComponent : public Component {
protected:
  std::shared_ptr<sf::Shape> _shape;
  sf::Vector2f _anchor;
  // sf::Shape _shape;

public:
  ShapeComponent() = delete;

  explicit ShapeComponent(Entity* p);

  void ShapeComponent::setAnchor(sf::Vector2f vec);

  void update(double dt) override;
  
  void render() override;
  
  sf::Shape& getShape() const;
  
  template <typename T, typename... Targs> void setShape(Targs... params) {
    _shape.reset(new T(params...));
  }
};