#pragma once

#include <SFML/Graphics/Text.hpp>
#include <ecm.h>

class TextComponent : public Component {
public:
  TextComponent() = delete;
  explicit TextComponent(Entity* p, const std::string& str = "");
  void update(double dt) override;

  void render() override;

  ~TextComponent() override;

  void setText(const std::string& str);
  void TextComponent::setAnchor(sf::Vector2f vec);
  sf::Vector2f TextComponent::getAnchoredPosition();

  void TextComponent::setSize(unsigned int size);

protected:
  std::shared_ptr<sf::Font> _font;
  std::string _string;
  sf::Text _text;
  sf::Vector2f _anchor;
};
